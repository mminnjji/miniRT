#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_hit_record t_hit_record;
typedef struct s_light  t_light;
typedef struct s_scene t_scene;
typedef struct s_material t_material;

typedef int             t_bool;
# define FALSE 0
# define TRUE 1

typedef int             t_object_type;
# define SP 0

# define LIGHT_POINT 1

# define EPSILON 1e-6 // 0.000001

# define LUMEN 3

struct s_vec3
{
    double x;
    double y;
    double z;
};

struct  s_ray
{
    t_point3    orig;
    t_vec3      dir;
};

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

struct s_material
{
	void *type;
}

struct s_hit_record
{
    t_point3    p;
    t_vec3      normal;
    double      tmin;
    double      tmax;
    double      t;
    t_bool      front_face;
	t_color3    albedo; // 반사율
	t_material	*material;
};

struct  s_scene
{
    t_canvas        canvas;
    t_camera        camera;
    t_object        *world;
    t_object        *light;
    t_color3        ambient;
    t_ray           ray;
    t_hit_record    rec;
};

struct  s_sphere
{
    t_point3    center;
    double      radius;
    double      radius2;
};


struct s_object
{
    t_object_type   type;
    void            *element;
    void            *next;
	t_color3        albedo;
};

struct      s_light
{
    t_point3    origin; //  광원 위치~
    t_color3    light_color; // 광원 세기 ~ (rgb별로)
    double      bright_ratio; 
};

double random_double();
t_vec3 random_on_hemisphere(t_vec3 normal);

#endif