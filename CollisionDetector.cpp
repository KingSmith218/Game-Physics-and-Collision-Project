// (c) Marco Gilardi, 2017
#include "CollisionDetector.h"
#include "Utils.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include "Contact.h"

#include<vector>
#include <iostream>

using namespace std;

CollisionData* CollisionDetector::CheckCollision(PhysicsEntity* obj1, PhysicsEntity* obj2)
{
	CollisionData* data = nullptr;

	if (dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr)
	{
		CollisionDetector::SphereSphereCollision(obj1, obj2, &data);
		return data;
	}
	
	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr) || 
		(dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr))
	{
		CollisionDetector::SphereAABBCollision(obj1, obj2, &data);
		return data;
	}

	if (dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr)
	{
		CollisionDetector::AABBAABBCollision(obj1, obj2, &data);
		return data;
	}

	return data;
}

vec2* CollisionDetector::SphereSphereContactPoint(PhysicsEntity* sph1, PhysicsEntity* sph2)
{
	vec2 * points = new vec2[1];
	vec2 v = sph2->getCollider()->getCenter() - sph1->getCollider()->getCenter();
	v = normalize(v);
	BoundingSphere* s = dynamic_cast<BoundingSphere*> (sph1->getCollider());
	points[0] = s->getRadii()*v;

	return points;
	
}

bool CollisionDetector::SphereSphereCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data) // we need to fill data so we need to pass a pointer to pointer
{
	BoundingSphere* s1 = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	BoundingSphere* s2 = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	
	float dist = Utils::distanceBetweenPoints(s1->getCenter(), s2->getCenter());
	float penetration = dist - (s1->getRadii() + s2->getRadii());
	bool collision = penetration <= 0;
	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];
		(*data)->contact->setManifold(SphereSphereContactPoint(obj1, obj2), 1);

		// check if any existing contact is not valid any more
		/*for (Contact &contact : manifold.contacts)
		{
			const Vec3 localToGlobalA =
				bodyA.LocalToGlobal(contact.localPositionA);

			const Vec3 localToGlobalB =
				bodyB.LocalToGlobal(contact.localPositionB);

			const Vec3 rAB =
				localToGlobalB - localToGlobalA;

			const Vec3 rA =
				contact.globalPositionA - localToGlobalA;

			const Vec3 rB =
				contact.globalPositionB - localToGlobalB;

			const const stillPenetrating =
				contact.normal.Dot(rAB) <= 0.0f;

			const rACloseEnough =
				rA.LengthSq() < persistentThresholdSq;
			const rBCloseEnough = rB.LengthSq() < persistentThresholdSq;

			// keep contact point if the collision pair is 
			// still colliding at this point, and the local 
			// positions are not too far from the global 
			// positions original acquired from collision detection
			if (rACloseEnough && rBCloseEnough)
			{
				// contact persistent, keep
				contact.persistent = true;
			}
			else
			{
				// contact invalid, remove
				manifold.Remove(contact);
			}
		}

		for (Contact &contact : manifold.contacts)
		{
			const Vec3 rA =
				newContact.globalPositionA - contact.globalPositionA;

			const Vec3 rB =
				newContact.globalPositionB - contact.globalPositionB;

			const bool rAFarEnough =
				rA.LengthSq() > persistentThresholdSq;

			const bool rBFarEnough =
				rB.LengthSq() > persistentThresholdSq;

			// proximity check  
			if (rAFarEnough && rBFarEnough)
				manifold.Add(newContact);
		}
			*/
		//Parameters* params = new Parameters(200, vec2(400, 240), vec2(0), 0.75f);
		//Parameters* params = new Parameters(0, vec2(SphereSphereContactPoint(obj1, obj2)->x, SphereSphereContactPoint(obj1, obj2)->y), vec2(0), .0f); //Fixed Object
		//Ball* ball = new  Ball(1.0f, params, vec3(0.0f, 1.0f, 0.0f));
		

		(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		(*data)->contact[0].setContactNormal(normalize(obj1->getParams()->transform.getPosition() - obj2->getParams()->transform.getPosition()));
		(*data)->contact[0].setRestitution(0.5f*(obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}

bool CollisionDetector::SphereAABBCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data)
{
	AABB* aabb;
	BoundingSphere* s = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	if (s != nullptr)
		aabb = dynamic_cast<AABB*>(obj2->getCollider());
	else
	{
		aabb = dynamic_cast<AABB*>(obj1->getCollider());
		s = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	}

	vec2 pointOnAABB = Utils::projectPointOnAABB(s->getCenter(), aabb);
	float dist = Utils::distanceBetweenPoints(s->getCenter(), pointOnAABB);
	float penetration = dist - s->getRadii();
	bool collision = penetration <= 0;
	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];
	//	(*data)->contact->setManifold(SphereSphereContactPoint(obj1, obj2), 1);

		(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		if (obj1->getParams()->getInvMass() < obj2->getParams()->getInvMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
			(*data)->contact[0].setContactNormal(-Utils::getAABBFaceNormal(s->getCenter(), aabb));
		}
		else
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
			(*data)->contact[0].setContactNormal(Utils::getAABBFaceNormal(s->getCenter(), aabb));
		}
		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}


bool CollisionDetector::AABBAABBCollision(PhysicsEntity * obj1, PhysicsEntity * obj2, CollisionData** data)
{
	AABB* aabb1 = dynamic_cast<AABB*>(obj1->getCollider());
	AABB* aabb2 = dynamic_cast<AABB*>(obj2->getCollider());

	vec2 aabb1ProjCenterX = aabb1->getCenter().x*Utils::right;
	vec2 aabb2ProjCenterX = aabb2->getCenter().x*Utils::right;
	float distX = Utils::distanceBetweenPoints(aabb1ProjCenterX, aabb2ProjCenterX);
	float penetrationX = distX - (aabb1->getRadii().x + aabb2->getRadii().x);
	bool collisionX = penetrationX <= 0;

	vec2 aabb1ProjCenterY = aabb1->getCenter().y*Utils::up;
	vec2 aabb2ProjCenterY = aabb2->getCenter().y*Utils::up;
	float distY = Utils::distanceBetweenPoints(aabb1ProjCenterY, aabb2ProjCenterY);
	float penetrationY = distY - (aabb1->getRadii().y + aabb2->getRadii().y);
	bool collisionY = penetrationY <= 0;
	bool collision = collisionX && collisionY;

	if (collision)
	{
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];
	//	(*data)->contact->setManifold(SphereSphereContactPoint(obj1, obj2), 1);

		vec2 point = aabb1->getCenter();
		AABB* aabb = aabb2;

		vec2 normal = -Utils::getAABBFaceNormal(point, aabb);
		if (obj1->getParams()->getInvMass() < obj2->getParams()->getInvMass())
		{
			point = aabb2->getCenter();
			aabb = aabb1;
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = Utils::getAABBFaceNormal(point, aabb);
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		vec2 penetrations = vec2(penetrationX, penetrationY);
		float penetration = dot(penetrations, abs(normal));
		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}
