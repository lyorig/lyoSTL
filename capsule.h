#pragma once

#include "lyostd_base.h"

/* CAPSULE.H:
   Vlastní implementace std::unique_ptr. */




LYOSTD_BEGIN
template <typename Ptr_type> class capsule {
public:
	capsule() : object{ nullptr }, refcount{ 1 } {}
	capsule(Ptr_type* obj) : object{ obj }, refcount{ 1 } {}
	capsule(const capsule& copy) : object{ copy.object }, refcount{ copy.refcount } { refcount++; }

	capsule& operator=(const capsule<Ptr_type>& copy)
	{
		if (this != &copy)
		{
			this->~capsule();

			object = copy.object;
			refcount++;
		}

		return *this;
	}

	~capsule() { if (refcount-- == 0) delete object; }

	Ptr_type* get()		   const { return object; }
	Ptr_type* operator->() const { return object; }
	Ptr_type& operator*()  const { return *object; }

private:
	Ptr_type* object;
	unsigned int refcount;
};
LYOSTD_END