#include "CollisionListener.h"

void CollisionListener::BeginContact(b2Contact* contact){
	Object* a = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* b = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
	a->beginCollision(b, contact);
	b->beginCollision(a, contact);
}

void CollisionListener::EndContact(b2Contact* contact){
	Object* a = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
	Object* b = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
	a->endCollision(b, contact);
	b->endCollision(a, contact);
}