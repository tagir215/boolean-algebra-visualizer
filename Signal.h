#ifndef SIGNAL
#define SIGNAL

class Signal{
public:
	virtual char getType() = 0;
	bool inverted = false;
	int x;
	int y;

	Signal(){
		x = 0;
		y=0;
	}
};

#endif
