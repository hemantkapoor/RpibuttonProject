#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

using namespace std;

int main()
{
	cout<<"Hello World\r\n";
	string evtFilePath(R"(/dev/input/event0)");
	input_event buttonInout;
	//Lets attempt to open the file
	int file_descr = open( evtFilePath.c_str(), O_RDONLY |O_NONBLOCK);
	if(file_descr < 0 )
	{
		cout<<"Cannot open "<< evtFilePath << endl;
		return -1;
	}
	//If here then we are ready to read
	for(auto time=0;time<1000;++time)
	{
		//cout<<"Reading Button Status\n";
		read(file_descr,&buttonInout,sizeof(buttonInout));
		//cout<<"Time = "<<buttonInout.time.tv_sec<<" Type = "<<buttonInout.type<<" code = "<<buttonInout.code<<" value = "<<buttonInout.value<<endl;
		if(buttonInout.type == 1)
		{
			if(buttonInout.value == 1)
			{
				cout<<"Button Pressed\n";
			}
			if(buttonInout.value == 0)
			{
				cout<<"Button Released\n";
			}
		}
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	close(file_descr);
	return 0;
}
