#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:
	int id;

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;

	DWORD dt;

	int _type;
	int _energy;

	vector<LPANIMATION> animations;
	LPANIMATION animation;

public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	void SetTrend(int nx) { this->nx = nx; }
	int GetTrend() { return nx; }

	int GetState() { return this->state; }

	int GetType() { return _type; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);// cài đặt tổng quát hơn AABB(chỉ xét 1 static 1 move)
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);//lọc ra các đối tượng có thể dụng
	void FilterCollision(//lựa 2 vật thể va chạm
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	void AddAnimation(int aniId);

	CGameObject(float _x = 0, float _y = 0, int type = 0);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;//do hình bao tùy thuộc trạng thái của đối tượng
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	int GetID() { return id; }
	void SetID(int id) { this->id = id; }

	int GetEnergy() { return _energy; }
	virtual void Hurt() { _energy -= 2; }
	virtual void Go(){}
	~CGameObject();
};

