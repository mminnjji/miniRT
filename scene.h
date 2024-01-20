#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "util.h"

typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;

// 내 눈에 대한 정보
struct  s_camera
{
    t_point3    orig;  // 내가 있는 위치
	// 내가 보는 입체 -> 이차원 변형할 뷰포트 == 캔버스
	// 캔버스 정보와 동일함
    double      viewport_h;
    double      viewport_w;
	// 눈에서 뷰포트까지의 수직거리
	double      focal_len;
    t_point3    left_bottom; // 왼쪽 아래 코너점
	// 뷰포트의 가로세로 방향벡터
    t_vec3      horizontal; // 가로
    t_vec3      vertical; // 세로
};

struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //가로 세로 비율
};

# include "trace.h"

typedef int             t_bool;
# define FALSE 0
# define TRUE 1

struct  s_sphere
{
    t_point3    center;
    double      radius;
    double      radius2;
};

struct s_hit_record
{
    t_point3    p; // 교점 좌표
    t_vec3      normal; // 법선 벡터
    double      tmin;
    double      tmax;
    double      t; // 원점 ~ 교점까지의 거리
    t_bool      front_face;
};

typedef int             t_object_type;
# define SP 0
struct	s_object
{
    t_object_type   type;
    void            *element;
    void            *next;
};

t_canvas    canvas(int  width, int height);
t_camera    camera(t_canvas *canvas, t_point3 origin);
t_color3    ray_color(t_ray *ray, t_object *world);
t_bool      hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
void        set_face_normal(t_ray *r, t_hit_record *rec);
t_object    *object(t_object_type type, void *element);
t_sphere    *sphere(t_point3 center, double radius);
#endif