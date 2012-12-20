/*A*�Թ���������*/
#include "AStar.h"
#include <stdio.h>
#include <math.h>

struct maze_map;
struct maze_node
{
	struct map_node _base;
	struct maze_map *_map;
	int value;
	/*�ڵ�ͼ�е�x,y����*/
	int x; 
	int y;	
};

#define BLOCK 2//�赲

int direction[8][2] = {
	{0,-1},//��
	{0,1},//��
	{-1,0},//��
	{1,0},//��
	{-1,-1},//����
	{1,-1},//����
	{-1,1},//����
	{1,1},//����
};

struct maze_map
{
	struct maze_node **_maze_map;
	int    max_x;
	int    max_y;
};

struct maze_node *get_mazenode_by_xy(struct maze_map *map,int x,int y)
{
	if(x < 0 || x >= map->max_x || y < 0 || y >= map->max_y)
		return NULL;
	return map->_maze_map[y][x];
}

//��õ�ǰmaze_node��8���ٽ��ڵ�,������赲��ᱻ����
struct map_node** maze_get_neighbors(struct map_node *mnode)
{
	struct map_node **ret = (struct map_node **)calloc(8,*ret);
	struct maze_node *_maze_node = (struct maze_node*)mnode;
	struct maze_map *_maze_map = _maze_node->_map;
	int32_t i = 0;
	int32_t c = 0;
	for( ; i < 8; ++i)
	{
		int x = _maze_node->x + direction[i][0];
		int y = _maze_node->x + direction[i][1];
		struct maze_node *tmp = get_mazenode_by_xy(_maze_map,x,y);
		if(tmp && tmp->value != BLOCK)
			ret[c++] = (struct map_node*)tmp;
	}
	return ret;
}

//���㵽�����ٽڵ���Ҫ�Ĵ���
double maze_cal_G_value(struct path_node *from,struct path_node *to)
{
	struct maze_node *_from = (struct maze_node*)from->_map_node;
	struct maze_node *_to = (struct maze_node*)to->_map_node;
	int delta_x = _from->x - _to->x;
	int delta_y = _from->y - _to->y;
	int i = 0;
	for( ; i < 8; ++i)
	{
		if(direction[i][0] == delta_x && direction[i][1] == delta_y)
			break;
	}
	if(i < 4)
		return 50.0f;
	else if(i < 8)
		return 60.0f;
	else
	{
		assert(0);
		return 0.0f;
	}	
}

double maze_cal_H_value(struct path_node *from,struct path_node *to)
{
	struct maze_node *_from = (struct maze_node*)from->_map_node;
	struct maze_node *_to = (struct maze_node*)to->_map_node;
	int delta_x = abs(_from->x - _to->x);
	int delta_y = abs(_from->y - _to->y);
	return (delta_x * 50.0f) + (delta_y * 50.0f);
}

struct maze_map* create_map(int **array,int max_x,int max_y)
{
	struct maze_map *_map = calloc(1,sizeof(*_map));
	_map->max_x = max_x;
	_map->max_y = max_y;
	_map->_maze_map = calloc(max_x,max_y,sizeof(struct maze_node*));
	int i = 0;
	int j = 0;
	for( ; i < max_y; ++i)
	{
		for( ; j < max_x ++j)
		{
			_map->_maze_map[i][j] = calloc(1,sizeof(struct maze_node));
			_map->_maze_map[i][j]->_map = _map;
			_map->_maze_map[i][j]->x = j;
			_map->_maze_map[i][j]->y = i;
			_map->_maze_map[i][j]->value = array[i][j];
		}
	}
	return _map;
}

int main()
{
	int array[15][25] =
	{
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,2},
		{2,0,0,2,0,0,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	};
	struct maze_map *map = create_map(array,25,15);
	struct map_node *from = (struct map_node*)get_mazenode_by_xy(map,1,1);
	struct map_node *to = (struct map_node*)get_mazenode_by_xy(map,4,1);
	struct A_star_procedure *astar = create_astar(maze_get_neighbors,maze_cal_G_value,maze_cal_H_value);
	struct path_node *path = find_path(astar,from,to);
	while(path)
	{
		struct maze_node *mnode = (struct maze_node *)path->_map_node;
		mnode->value = 1;
		path = paht->parent;
	}
	//���´�ӡ��ͼ��·��
	int i = 0;
	int j = 0;
	for(; i < 15; ++i)
	{
		for(; j < 25; ++j)
		{
			printf("%d",map->_maze_map[i][j]->value);
		}
		printf("\n");
	}
	return 0;
}

