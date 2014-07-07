#ifndef _SHIFTER
#define _SHIFTER

class shifter_base {
public:
	long shift_start_time;
	long in_this_many_msec;
	void* addr;
	virtual void shift() = 0;
	bool operator==(shifter_base& rhs) {
		return (addr == rhs.addr);
	}
	virtual ~shifter_base() {};
};

class shiftreg {
	std::list<shifter_base*> shifter_pointers;
public:
	void add(shifter_base* sh) {
		//dont put in finished shifters
		long time = glutGet(GLUT_ELAPSED_TIME);
		if(sh->shift_start_time + sh->in_this_many_msec < time) {
			delete sh;
			return;
		}

		//dont put in duplicates
		for(std::list<shifter_base*>::iterator i = shifter_pointers.begin(); i != shifter_pointers.end(); ++i) {
			if((*i)->addr == sh->addr) {
				delete sh;
				return;
			}
		}
		//put in everything else
		shifter_pointers.push_back(sh);
	}
	void shift() {
		long time = glutGet(GLUT_ELAPSED_TIME);
		//delete old shifters
		for(std::list<shifter_base*>::iterator i = shifter_pointers.begin(); i != shifter_pointers.end(); ++i) {
			if((*i)->shift_start_time + (*i)->in_this_many_msec < time) {
				(*i)->shift();
				delete (*i);
				shifter_pointers.erase(i);
				//iterators tend to cause segfaults if elements are deleted while running
				//start over with new iterator to avoid
				i = shifter_pointers.begin();
			}
			else {
				(*i)->shift();
			}
		}
	}
};

template<class T>
class shifter : public shifter_base {
	T* what_to_shift;
	T shift_from;
	T shift_into;
public:
	shifter(T* _what_to_shift, T _shift_into, long _in_this_many_msec, long when_to_start = 0) {
		addr = _what_to_shift;
		if(when_to_start == 0)
			shift_start_time = glutGet(GLUT_ELAPSED_TIME);
		else
			shift_start_time = when_to_start;

		in_this_many_msec = _in_this_many_msec;
		what_to_shift = _what_to_shift;
		shift_from = *_what_to_shift;
		shift_into = _shift_into;
	}
	void shift() {
		if(in_this_many_msec == 0) {
			*what_to_shift = shift_into;
		}
		long current_time = glutGet(GLUT_ELAPSED_TIME);
		if(shift_start_time > current_time) {
			shift_from = *what_to_shift;
			return;
		}

		current_time -=  shift_start_time;
		float ratio = (float)current_time / in_this_many_msec;
		if(ratio > 1) ratio = 1;
		*what_to_shift = (shift_from * (1 - ratio) + shift_into * ratio);
	}
};

#endif
