#include "ps4.h"
#include "patch.h"


void blockHistory()
{
	char hfile[256], umsg[256]; 
	SceUserServiceLoginUserIdList userIdList;
	userIdList = getUserIDList();
	for (int i = 0; i < SCE_USER_SERVICE_MAX_LOGIN_USERS; i ++) 
	{
		if (userIdList.userId[i] != -1 && userIdList.userId[i] != 0) 
		{
			sprintf(hfile, "/user/home/%x/webbrowser/endhistory.txt", userIdList.userId[i]);
			if (!file_exists(hfile) && !dir_exists(hfile))
			{
				mkdir(hfile, 0777);
				sprintf(umsg, "History Block: Enabled\nFor: %s\n\nRun payload again to disable", getUserName(userIdList.userId[i]));
				systemMessage(umsg);
			}
			else
			{
				if (dir_exists(hfile))
				{
					rmdir(hfile);
					sprintf(umsg, "History Block: Disabled\nFor: %s\n\nRun payload again to enable", getUserName(userIdList.userId[i]));
					systemMessage(umsg);
				}
				else if (file_exists(hfile))
				{
					unlink(hfile);
					mkdir(hfile, 0777);
					sprintf(umsg, "History Block: Enabled\nFor: %s\n\nRun payload again to disable", getUserName(userIdList.userId[i]));
					systemMessage(umsg);
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