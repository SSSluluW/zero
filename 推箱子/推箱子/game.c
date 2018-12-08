#include"function.h"

void init() {

	//该段代码功能是隐藏光标，调用了win32编程接口，不需要掌握
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取窗口句柄
	CONSOLE_CURSOR_INFO cci;//实列化一个控制台光标信息类
	GetConsoleCursorInfo(hOut, &cci);//获取光标信息
	cci.bVisible = FALSE;//隐藏光标
	SetConsoleCursorInfo(hOut, &cci);//设置光标信息

	system("title 推箱子1.0");//设定窗口名称
	system("mode con cols=120 lines=30");//设定窗口大小
}

void mainloop() {
	int level;
	int level_option;
	int scenes;
	char option;
	int isEnd;

	level = 0;
	level_option = 1;
	scenes = 0;
	isEnd = 0;

	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    开始(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   退出(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};


	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   从头开始(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    选关(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    返回(R)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|"
	};


	while (1) {
		system("cls");
		switch (scenes) {
		case 0:
		
			for (int i = 0; i < 11; i++)
				puts(main_interface[i]);
			break;
		case 1:
		
			for (int i = 0; i < 11; i++)
				puts(menu2[i]);
			break;
		case 2:
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("请选择关卡(1-%d):%d", maps_num, level_option);
			break;
		default:
			break;
		}


		if (scenes < 3) {
			option = getch();
			option = tolower(option);
		}

		//事件判定
		switch (scenes) {
		case 0:
			if (option == 's')
				scenes = 1;
			else if (option == 27) {
				isEnd = 1;
			}
			break;
		case 1:
			if (option == 'r' || option == 27)
				scenes = 0;
			else if (option == 'a') {
				scenes = 3;
			}
			else if (option == 'x') {
				scenes = 2;
			}
			break;
		case 2:
			  
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 13 || option == 32)) {
				level = level_option;
				scenes = 4;
			}
			else if (option == 27)
				scenes = 1;
			break;
		case 3:
			level = 0;
			scenes = gameloop(level);
			break;
		case 4:
			scenes = gameloop(level);
			break;
		case 5:
			level++;
			scenes = 4;
			break;
		case 6:
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}

		if (isEnd)
			break;
	}
}

int gameloop(int level) {

	//init
	int x = 0;
	int y = 0;
	char key = 0;
	int isEnd = 0;
	int reValue;
	int scenes = 0;
	Map *map;
	map = LoadMap(level);
	x = map->x;
	y = map->y;

	while (1) {

		system("cls");
		switch (scenes) {
		case 0:
			printf("\n\n\n\n\t\t\t\t\t\t       第%d关", level);
			printf("\n\n");
			
			for (int i = 0; i < map->h; i++)
			{
				for (int j = 0; j < 52; j++)
					printf(" ");
				puts(map->map[i]);
			}
			printf("\n\n\t\t\t\t\t      重玩本关(Q)  菜单(ESC)");
			break;
		case 1:
			printf("\n\n\n\n\n\t\t\t\t\t\t       继续(R)\n");
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t            重玩(Q)  下一关(N)  \n");
			else
				printf("\n\n\t\t\t\t\t\t  重玩(Q)  下一关(N)    \n");
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			break;
		case 2:
			if (level == maps_num - 1)
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t这已经是最后一关了！");
			else
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  过关!");
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t\t    重玩(Q)   \n");
			else
				printf("\n\n\t\t\t\t\t    重玩(Q)  下一关(N)\n");
			break;
		default:
			break;
		}
		key = getch();

		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'W':
			case 'w':
				switch (map->map[y - 1][x])
				{
				case ' ':
				case 'X':
					map->map[y - 1][x] = '@';
					map->map[y][x] = ' ';
					y = y - 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y - 2][x] != '#'&&map->map[y - 2][x] != 'O'&&map->map[y - 2][x] != 'Q') {
						if (map->map[y - 2][x] == 'X')
							map->map[y - 2][x] = 'Q';
						else
							map->map[y - 2][x] = 'O';
						map->map[y - 1][x] = '@';
						map->map[y][x] = ' ';
						y = y - 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'S':
			case 's':

				switch (map->map[y + 1][x])
				{
				case ' ':
				case 'X':
					map->map[y + 1][x] = '@';
					map->map[y][x] = ' ';
					y = y + 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y + 2][x] != '#'&&map->map[y + 2][x] != 'O'&&map->map[y + 2][x] != 'Q') {
						if (map->map[y + 2][x] == 'X')
							map->map[y + 2][x] = 'Q';
						else
							map->map[y + 2][x] = 'O';

						map->map[y + 1][x] = '@';
						map->map[y][x] = ' ';
						y = y + 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'A':
			case 'a':
				switch (map->map[y][x - 1])
				{
				case ' ':
				case 'X':
					map->map[y][x - 1] = '@';
					map->map[y][x] = ' ';
					x = x - 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x - 2] != '#'&&map->map[y][x - 2] != 'O'&&map->map[y][x - 2] != 'Q') {
						if (map->map[y][x - 2] == 'X')
							map->map[y][x - 2] = 'Q';
						else
							map->map[y][x - 2] = 'O';
						map->map[y][x - 1] = '@';
						map->map[y][x] = ' ';
						x = x - 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'D':
			case 'd':
				switch (map->map[y][x + 1])
				{
				case ' ':
				case 'X':
					map->map[y][x + 1] = '@';
					map->map[y][x] = ' ';
					x = x + 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x + 2] != '#'&&map->map[y][x + 2] != 'O'&&map->map[y][x + 2] != 'Q') {
						if (map->map[y][x + 2] == 'X')
							map->map[y][x + 2] = 'Q';
						else
							map->map[y][x + 2] = 'O';
						map->map[y][x + 1] = '@';
						map->map[y][x] = ' ';
						x = x + 1;
					}
					break;

				default:
					break;
				}
				break;
			case 'R':
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;

				break;
			case'q':
				reValue = 4;
				isEnd = 1;
			case 27:

				scenes= 1;
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (key)
			{
			case 'R':
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;

				break;
			case 'N':
			case 'n':
				scenes = 0;
				map = LoadMap(map->level+1);
				level += 1;
				x = map->x;
				y = map->y;
				break;
			case'q':
			reValue = 4;
            isEnd = 1;
			case 27:
				isEnd = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		int isOver = 1;
		switch (scenes)
		{
		case 0:


			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] != 'Q')
					isOver = 0;
			}
			if (isOver)
				scenes = 1;

			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] == ' ')
					map->map[map->aimy[i]][map->aimx[i]] = 'X';
			}

			break;
		case 1:
		
			break;
		default:
			break;
		}
		if (isEnd)
			break;
	}
	return reValue;
}

Map* LoadMap(int level) {

	Map *temp = (Map*)malloc(sizeof(Map));
	char buffer[256];

	FILE *fp;
	sprintf(buffer, "data/Map/%d.txt", level);
	fp = fopen(buffer, "r");

	temp->level = level;
	temp->aim_count = 0;

	for (int i = 0;; i++) {
		fgets(temp->map[i], 256, fp);

		temp->map[i][strlen(temp->map[i]) - 1] = '\0';

		for (int j = 0; temp->map[i][j] != '\0'; j++) {
			switch (temp->map[i][j]) {
			case '@':
				temp->x = j;
				temp->y = i;
				break;
			case 'X':
			case 'Q':
				temp->aimx[temp->aim_count] = j;
				temp->aimy[temp->aim_count] = i;

				temp->aim_count++;
				break;
			}

		}

		if (temp->map[i][1] == '|')
		{
			temp->map[i][1] = '=';
			temp->h = i + 1;
			break;
		}
	}

	fclose(fp);
	return temp;
}
