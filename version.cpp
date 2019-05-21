#include <Core/Core.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
using namespace std;

int main(int argc, const char *argv[])
{
	std::cout << "number Arg : " <<argc <<"\n";
	std::cout << "Args  : " <<argv[0] <<"\n";
	if(argc >0 && Upp::String(argv[0]).Find("@" ) != -1 ){
		Upp::String arg = Upp::String(argv[0])  ;
		arg.Replace("@"," ");
		Upp::String exeToLaunch = arg.Left(arg.Find(";"));
		Upp::String WhereToGet =arg.Right(arg.GetCount()-(arg.Find(";")+1));
			if(CopyFile(WhereToGet.ToStd().c_str(),exeToLaunch.ToStd().c_str(),FALSE) != FALSE) { //Upp::FileCopy(WhereToGet.ToStd().c_str(),exeToLaunch.ToStd().c_str())
			    STARTUPINFO si;
			    PROCESS_INFORMATION pi;
			    ZeroMemory( &si, sizeof(si) );
			    si.cb = sizeof(si);
			    ZeroMemory( &pi, sizeof(pi) );
			    // Start the child process. */
			    std::cout << "process creation ! \n";
				if( CreateProcess(exeToLaunch.ToStd().c_str(),   // No module name (use command line)
							       	NULL,        // Command line
							        NULL,           // Process handle not inheritable
							        NULL,           // Thread handle not inheritable
							        FALSE,          // Set handle inheritance to FALSE
							        0,              // No creation flags
							        NULL,           // Use parent's environment block
							        NULL,           // Use parent's starting directory 
							        &si,            // Pointer to STARTUPINFO structure
							        &pi )           // Pointer to PROCESS_INFORMATION structure
							    ) 
				{ 
					WaitForSingleObject(pi.hProcess,INFINITE);
					CloseHandle( pi.hProcess );
    				CloseHandle( pi.hThread );
					cout << "succes !" <<"\n";
				} 
				else
				{
					cout <<"error"<<"\n";
				}                       
			}
	}
}
