/* Demo of assymetrical double dispatch - dispatch events to processors, where
the event-handling function is specified by the combination of event type and processor type.
Using the method of virtual functions that call overloaded functions.

For brevity, this demo has in one file declarations and definitions that would normally be
in several files, as noted below.
*/
#include <iostream>
#include <list>
#include <cstdlib>	// for rand function

using namespace std;

// Class Declarations first - these would normally be in separate header files

// incomplete declaration of Processor
class Processor;
// base class of Events containing a send-yourself virtual function
// and a static counter to give each event an id number
class Event {
public:
	Event() : id(++count) {}
	virtual void send_self(Processor *) {}
	int get_id() {return id;}
private:
	int id;
	static int count;
};

// Two classes of Events
class A_event : public Event {
public:
	virtual void send_self(Processor *);
};

class B_event : public Event {
public:
	virtual void send_self(Processor *);
};

// The Processor base class has virtual functions overloaded
// to handle each type of event. These functions do nothing in base class
// so that if a processor doesn't override the handler, then it
// doesn't care to respond to that type of event
class Processor {
public:
	virtual void handle_event(A_event *) {}
	virtual void handle_event(B_event *) {}
};

// Two classes of processor will respond differently to the events
// using virtual functions with a parameter for each event type.
class Processor1 : public Processor {
public:
	virtual void handle_event(A_event *);
	virtual void handle_event(B_event *);
};

class Processor2 : public Processor {
public:
	virtual void handle_event(A_event *);
	virtual void handle_event(B_event *);
};

// Implementations - these would normally be in a .cpp file for each Event type
int Event::count = 0;	// the static counter

// Event self-dispatch - in a .cpp file for each event type
void A_event::send_self(Processor * p)
{
	// send this event to the designated processor
	p->handle_event(this);
}

// Event self-dispatch
void B_event::send_self(Processor * p)
{
	// send this event to the designated processor
	p->handle_event(this);
}

// Processor event handlers - these would normally be in a .cpp file for each Processor type
// Processor1 handles each event type
void Processor1::handle_event(A_event *  e)
{
	cout << "Processor1 handles A_event " << e->get_id() << endl;
}

void Processor1::handle_event(B_event *  e)
{
	cout << "Processor1 handles B_event " << e->get_id() << endl;
}

// Processor2 reacts more emotionally!
void Processor2::handle_event(A_event *  e)
{
	cout << "Processor2 is overjoyed to get A_event " << e->get_id() << endl;
}

void Processor2::handle_event(B_event *  e)
{
	cout << "Processor2 hates getting B_event " << e->get_id() << endl;
}

// Main function - would be in a .cpp of its own - Demos the double dispatch
void fill_event_list(list<Event *>& events);

int main() 
{
	// create a list of processors
	list<Processor *> processors;
	processors.push_back(new Processor1);
	processors.push_back(new Processor2);
	
	// create a list of events
	list<Event *> events;
	fill_event_list(events);
	
	// now dispatch each event to each processor
	for(list<Event *>::iterator event_it = events.begin(); event_it != events.end(); ++event_it) {
			// for clarity, get a pointer to the event
			Event * event_ptr = *event_it;
		for(list<Processor *>::iterator processor_it = processors.begin(); processor_it != processors.end(); ++processor_it) {
			// for clarity, get a pointer to the processor
			Processor * processor_ptr = *processor_it;
			// now start the double dispatch by having the event send itself to the processor
			event_ptr->send_self(processor_ptr);
			}
		// finished with the event, so delete it
		delete event_ptr;
		}
	
	// clean up the processors - neatness counts!
	for(list<Processor *>::iterator processor_it = processors.begin(); processor_it != processors.end(); ++processor_it) {
		delete *processor_it;
		}
}

// create a series of events, randomly chosen by type
void fill_event_list(list<Event *>& events)
{
	for(int i = 0; i < 5; i++) {
		if(double(rand())/RAND_MAX < .5)	// flip a coin
			events.push_back(new A_event);
		else
			events.push_back(new B_event);
		}
}

/* Sample output - each processor responds differently to each event type
Processor1 handles A_event 1
Processor2 is overjoyed to get A_event 1
Processor1 handles A_event 2
Processor2 is overjoyed to get A_event 2
Processor1 handles B_event 3
Processor2 hates getting B_event 3
Processor1 handles A_event 4
Processor2 is overjoyed to get A_event 4
Processor1 handles B_event 5
Processor2 hates getting B_event 5
*/


