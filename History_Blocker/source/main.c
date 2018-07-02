#include "ps4.h"
#include "patch.h"


void blockHistory()
{
	char hfile[256]; 
	DIR *dir = opendir("/user/home/");
    if (dir)
	{
		struct dirent *dp;
		struct stat info;
		while ((dp = readdir(dir)) != NULL)
		{
			if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			{}
			else
			{
				sprintf(hfile, "/user/home/%s/webbrowser/endhistory.txt", dp->d_name);	
				if (!file_exists(hfile) && !dir_exists(hfile))
				{
					mkdir(hfile, 0777);
					systemMessage("History Block: Enabled\n\nRun payload again to disable");
				}
				else
				{
					if (!stat(hfile, &info))
					{
						if (S_ISDIR(info.st_mode))
						{
							rmdir(hfile);
							systemMessage("History Block: Disabled\n\nRun payload again to enable");
						}
						else if (S_ISREG(info.st_mode))
						{
							unlink(hfile);
							mkdir(hfile, 0777);
							systemMessage("History Block: Enabled\n\nRun payload again to disable");
						}	
					}
				}
			}
		}
	}
}


int _main(struct thread *td) {
	initKernel();
	initLibc();
	syscall(11,patcher,td);
    initSysUtil();
	blockHistory();
	return 0;
}