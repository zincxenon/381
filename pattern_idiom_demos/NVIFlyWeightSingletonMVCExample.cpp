/* Sketch code showing use of some design patterns in combination.
The overall context is a Model-View-Controller pattern. 

A particular type of View is VisualView. It has a container of VisualViewObjects. 
Each VisualViewObject has data about the color, location, etc 
of an object to be drawn in a window, including a pointer to 
a Flyweight Drawing_shape. 

One of each type of Flyweight Drawing_shape is kept in a Singleton
container; when the shape for a VisualViewObject is specified, the 
pointer is fetched from the Singleton shape pool and stored in the 
VisualViewObject. 

When it is time to draw the shapes, each VisualViewObject is told to
draw itself. It delegates this to the Drawing_shape by calling 
the Non-Virtual Interface function in Drawing_shape. This function
allows each type of drawing shape to customize its behavior by means
of private virtual functions.
*/

// The VisualViewObject class
class VisualViewObject {
public:
	VisualViewObject(CGPoint location_, CGSize size_, 
		const Symbol& label_, CGColorRef color_, const Symbol& shape_);

	void set_location(CGPoint location_)
		{location = location_;}

	void set_shape(const Symbol& shape_);

	void drawself(CGContextRef ctx, float scale) const;
private:
	CGPoint location;

	CGColorRef color;

	Drawing_shape * shape_ptr;

};

// The VisualView class
class VisualView : public AppDrawingWindow, public View_base {
public:
	VisualView(CFStringRef window_name);

	// called from base class to redraw the window
	virtual void draw_content(CGContextRef ctx);


	// notifications from Model

	virtual void notify_visual_location_changed(const Symbol& object_name, GU::Point location);


private:

	typedef std::map<Symbol, VisualViewObject *> objects_t;
	objects_t objects;

};

// VisualView, when notified that a particular object has changed location, sets
// the location of the corresponding VisualViewObject
void VisualView::notify_visual_location_changed(const Symbol& object_name, GU::Point location)
{
	VisualViewObject * ptr = objects[object_name];
	if(ptr)
		ptr->set_location(location.x, location.y);

}
	
// VisualView, when notified that a particular object has changed shape, sets
// the shape of the corresponding VisualViewObject by calling this function
// which gets the Flyweight shape pointer from the Singleton shape pool
void VisualViewObject::set_shape(const Symbol& shape_)
{
	shape_ptr = Drawing_shape_pool::get_instance().get_shape_ptr(shape_);
}

// VisualView draws its content by telling each VisualViewObject to draw itself
void VisualView::draw_content(CGContextRef ctx)
{	

	
	for(objects_t::iterator it = objects.begin(); it != objects.end(); ++it)
		(it->second)->drawself(ctx, scale);

}

// VisualViewObject draws itself by calling the Flyweight's draw function
// with itself as a parameter
void VisualViewObject::drawself(CGContextRef ctx, float scale) const
{

	shape_ptr->draw(ctx, this);

}

// The base of the Flyweight class hierarchy, with draw being the NonVirtual Interface function
// Drawing each shape requires a setup of the drawing context, a drawself of creating the basic shape,
// and a finish of putting the actual shape into the drawing context.
class Drawing_shape {
public:
	void draw(CGContextRef ctx, const VisualViewObject * const obj_ptr) const
			{
			setup(ctx, obj_ptr);
			drawshape(ctx, obj_ptr);
			finish(ctx, obj_ptr);
			}
	virtual ~Drawing_shape() {}
protected:
	virtual void setup(CGContextRef ctx, const VisualViewObject * const obj_ptr) const = 0;
	virtual void drawshape(CGContextRef ctx, const VisualViewObject * const obj_ptr) const = 0;
	virtual void finish(CGContextRef ctx, const VisualViewObject * const obj_ptr) const = 0;	
};

// A major subclass of Drawing_shapes which have interiors, and may or may not be filled - a read-only member determines this
class Drawing_shape_fillable : public Drawing_shape {
public:
	Drawing_shape_fillable(bool filled_) : filled(filled_) {}
protected:
	virtual void setup(CGContextRef ctx, const VisualViewObject * const obj_ptr) const;			// set initial stroke colors
	virtual void finish(CGContextRef ctx, const VisualViewObject * const obj_ptr) const;		// stroke the path
	bool get_filled() const {return filled;}
private:
	bool filled;
};

// The customizations for fillable Drawing_shapes.
void Drawing_shape_fillable::setup(CGContextRef ctx, const VisualViewObject * const obj_ptr) const
{
	CGContextSaveGState(ctx);
	
	// if disappearing, make the colors transparent
	if(obj_ptr->get_disappearing())
		CGContextSetAlpha(ctx, 0.3);
	else
		CGContextSetAlpha(ctx, 1.0);
	// the stroke and fill colors are the same as the object color
	CGContextSetStrokeColorWithColor(ctx, obj_ptr->get_color());
	// set the fill color
	if(get_filled()) {
		CGContextSetLineWidth(ctx, 2./20.);
		CGContextSetFillColorWithColor(ctx, obj_ptr->get_color());
		}
	else {
		CGContextSetLineWidth(ctx, 2./20.);
		}
}

// either draw the path as filled or not
void Drawing_shape_fillable::finish(CGContextRef ctx, const VisualViewObject * const obj_ptr) const
{
	if(get_filled())
		CGContextDrawPath(ctx, kCGPathFillStroke);
	else
		CGContextStrokePath(ctx);
	
	CGContextRestoreGState(ctx);	// restore the global alpha
}

// A Triangle is a basic shape that can be filled or not
class Triangle_shape : public Drawing_shape_fillable {
public:
	Triangle_shape(bool filled_) : Drawing_shape_fillable(filled_) {}
	virtual void drawshape(CGContextRef ctx, const VisualViewObject * const obj_ptr) const;
};

// create the triangle shape as a path
void Triangle_shape::drawshape(CGContextRef ctx, const VisualViewObject * const obj_ptr) const
{
	CGRect rect = center_size_to_CGRect(obj_ptr->get_location(), obj_ptr->get_size());
    CGContextBeginPath(ctx);
	CGContextMoveToPoint(ctx, rect.origin.x, rect.origin.y);				// goto bottom left
	CGContextAddLineToPoint(ctx, CGRectGetMidX(rect), CGRectGetMaxY(rect));	// go to top center
	CGContextAddLineToPoint(ctx, CGRectGetMaxX(rect), CGRectGetMinY(rect));	// go to bottom right
	CGContextClosePath(ctx);
}

// A singleton containing a pool of DrawingShapes keyed by Shape Name, a Symbol
class Drawing_shape_pool {
public:
	static Drawing_shape_pool& get_instance();
	// get flyweight object from shape name
	Drawing_shape * get_shape_ptr(const Symbol& shape) const;
private:
	Drawing_shape_pool();
	~Drawing_shape_pool();
	typedef std::map<Symbol, Drawing_shape *> shape_map_t;
	shape_map_t shape_map;
};

// a Meyers singleton
Drawing_shape_pool& Drawing_shape_pool::get_instance()
{
	static Drawing_shape_pool the_shape_map;
	return the_shape_map;
}

// how the pool is initialized
Drawing_shape_pool::Drawing_shape_pool()
{
	shape_map[Circle_c] = 			new Circle_shape(true);
	shape_map[Empty_Circle_c] =		new Circle_shape(false);

}


