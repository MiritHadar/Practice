/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>  /* printf */
#include <string.h>	/* memcpy */
#include <stdlib.h>	/* malloc, free */

/*****************************ForwardDeclerations*********************************/
struct PublicTransport;
void PublicTransport_Ctor_V(struct PublicTransport *const this_);
void PublicTransport_CCtor_PT(struct PublicTransport *const this, const struct PublicTransport *const other_);
void PublicTransport_display_V(struct PublicTransport *const this);
void PublicTransport_print_count_V();
int PublicTransport_get_ID_V(struct PublicTransport *const this);
void PublicTransport_Dtor_V(struct PublicTransport *const this);
void (*vTable_PT[])(struct PublicTransport *const this_) = {PublicTransport_Dtor_V, PublicTransport_display_V};

struct Minibus;
void Minibus_Ctor_V(struct Minibus *const this);
void Minibus_CCtor_M(struct Minibus *const this, const struct Minibus *const other_);
void Minibus_display_V(struct Minibus *const this);
void Minibus_wash_I(struct Minibus *const this, int minutes);
void Minibus_Dtor_V(struct Minibus *const this);
void (*vTable_Minibus[])(struct Minibus *const) = {Minibus_Dtor_V, Minibus_display_V, (void(*)(struct Minibus *const))Minibus_wash_I};

struct Taxi;
void Taxi_Ctor_V(struct Taxi *const this);
void Taxi_CCtor_T(struct Taxi *const this, const struct Taxi *const other_);
void Taxi_display_V(struct Taxi *const this);
void Taxi_Dtor_V(struct Taxi *const this);
void (*vTable_Taxi[])(struct Taxi *const) = {Taxi_Dtor_V, Taxi_display_V};

struct SpecialTaxi;
void SpecialTaxi_Ctor_V(struct SpecialTaxi *const this);
void SpecialTaxi_CCtor_ST(struct SpecialTaxi *const this, const struct SpecialTaxi *const other_);
void SpecialTaxi_display_V(struct SpecialTaxi *const this);
void SpecialTaxi_Dtor_V(struct SpecialTaxi *const this);
void (*vTable_ST[])(struct SpecialTaxi *const) = {SpecialTaxi_Dtor_V, SpecialTaxi_display_V};

int max_func_T(const int *t1, const int *t2);
void print_info_PT(struct PublicTransport *const a);
void print_info_v();
void print_info_Minibus(struct Minibus *const m);
void print_info_int(int i, struct PublicTransport *out);
void taxi_display_T(struct Taxi *s);
void *new(size_t size);
void *new_arr(size_t size);
void delete(void *ptr_to_data);
void delete_arr(void *ptr_to_data);

struct PublicConvoy;
void PublicConvoy_Ctor_V(struct PublicConvoy *const this);
void  PublicConvoy_CCtor_PC(struct PublicConvoy *const this,
							const struct PublicConvoy *const other_);
void  PublicConvoy_display_V(struct PublicConvoy *const this);
void  PublicConvoy_Dtor_V(struct PublicConvoy *const this);
void (*vTable_PC[2])(struct PublicConvoy *const) = { PublicConvoy_Dtor_V,  PublicConvoy_display_V};
/************************************PublicTransport***********************************/
struct PublicTransport
{
	void (**m_vTable)(struct PublicTransport *const);
	int m_license_plate_PT;
};

int PublicTransport_s_count = 0;

void PublicTransport_Ctor_V(struct PublicTransport *const this)
{
	this->m_vTable = vTable_PT;
	this->m_license_plate_PT = ++PublicTransport_s_count;
	printf("PublicTransport::Ctor()%d\n", this->m_license_plate_PT);
}

void PublicTransport_CCtor_PT(struct PublicTransport *const this, const struct PublicTransport *const other_)
{
	this->m_vTable = vTable_PT;

	this->m_license_plate_PT = ++PublicTransport_s_count;
	printf("PublicTransport::CCtor() %d\n", this->m_license_plate_PT);
}

void PublicTransport_display_V(struct PublicTransport *const this)
{
	printf("PublicTransport::display(): %d\n", this->m_license_plate_PT);
}

void PublicTransport_print_count_V()
{
	printf("s_count: %d\n", PublicTransport_s_count);
}

int PublicTransport_get_ID_V(struct PublicTransport *const this)
{
	return this->m_license_plate_PT;
}

void PublicTransport_Dtor_V(struct PublicTransport *const this)
{
	this->m_vTable = vTable_PT;

	--PublicTransport_s_count;
	printf("PublicTransport::Dtor()%d\n", this->m_license_plate_PT);
}

/************************************Minibus***********************************/
struct Minibus
{
	struct PublicTransport m_PublicTransport;
	int m_numSeats_M;
};

void Minibus_Ctor_V(struct Minibus *const this)
{
	PublicTransport_Ctor_V(&this->m_PublicTransport);
	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Minibus;
	this->m_numSeats_M = 20;
	printf("Minibus::Ctor()\n");
}

void Minibus_CCtor_M(struct Minibus *const this, const struct Minibus *const other_)
{
	PublicTransport_CCtor_PT(&this->m_PublicTransport, &other_->m_PublicTransport);  
  	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Minibus;
	this->m_numSeats_M = other_->m_numSeats_M;
	printf("Minibus::CCtor()\n");
}

void Minibus_Dtor_V(struct Minibus *const this)
{
	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Minibus;
	printf("Minibus::Dtor()\n");
	PublicTransport_Dtor_V(&this->m_PublicTransport);
}

void Minibus_display_V(struct Minibus *const this)
{
	printf("Minibus::display() ID:%d", PublicTransport_get_ID_V(&(this->m_PublicTransport)));
	
    printf(" num seats:%d\n", this->m_numSeats_M);
}

void Minibus_wash_I(struct Minibus *const this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransport_get_ID_V(&(this->m_PublicTransport)));
}

/************************************Taxi***********************************/
struct Taxi
{
	struct PublicTransport m_PublicTransport;
};

void Taxi_Ctor_V(struct Taxi *const this)
{
	PublicTransport_Ctor_V(&this->m_PublicTransport);
	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Taxi;
	printf("Taxi::Ctor()\n");
}

void Taxi_CCtor_T(struct Taxi *const this, const struct Taxi *const other_)
{
	PublicTransport_CCtor_PT(&this->m_PublicTransport, &other_->m_PublicTransport);
	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Taxi;

	printf("Taxi::CCtor()\n");
}

void Taxi_Dtor_V(struct Taxi *const this)
{
	this->m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_Taxi;
	printf("Taxi::Dtor()\n");
	PublicTransport_Dtor_V(&this->m_PublicTransport);
}

void Taxi_display_V(struct Taxi *const this)
{
	printf("Taxi::display() ID:%d\n", PublicTransport_get_ID_V(&(this->m_PublicTransport)));
}

/*********************************SpecialTaxi***********************************/

struct SpecialTaxi
{
	struct Taxi m_Taxi;
};

void SpecialTaxi_Ctor_V(struct SpecialTaxi *const this)
{
	Taxi_Ctor_V(&this->m_Taxi);
	this->m_Taxi.m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_ST;

	printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_CCtor_ST(struct SpecialTaxi *const this, const struct SpecialTaxi *const other_)
{
	PublicTransport_CCtor_PT(&(this->m_Taxi.m_PublicTransport), &(other_->m_Taxi.m_PublicTransport));
	this->m_Taxi.m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_ST;
	printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_display_V(struct SpecialTaxi *const this)
{
	printf("SpecialTaxi::display() ID:%d\n", PublicTransport_get_ID_V(&(this->m_Taxi.m_PublicTransport)));
}
void SpecialTaxi_Dtor_V(struct SpecialTaxi *const this)
{
	this->m_Taxi.m_PublicTransport.m_vTable = (void(**)(struct PublicTransport *const))vTable_ST;
	printf("SpecialTaxi::Dtor()\n");
	Taxi_Dtor_V(&this->m_Taxi);
}

/**********************************PublicConvoy**************************************/
struct PublicConvoy
{
	struct PublicTransport m_publicTransport;
	struct PublicTransport *m_pt1;
    struct PublicTransport *m_pt2;
    struct Minibus m_m;
    struct Taxi m_t;
};

void PublicConvoy_Ctor_V(struct PublicConvoy *const this)
{
	this->m_publicTransport.m_vTable = (void(**)(struct PublicTransport*))vTable_PC;
	PublicTransport_Ctor_V(&this->m_publicTransport);
	/* MIL */
	this->m_pt1 = (struct PublicTransport*)new(sizeof(struct Minibus));
	Minibus_Ctor_V((struct Minibus*)this->m_pt1);

	this->m_pt2 = (struct PublicTransport*)new(sizeof(struct Taxi));
	Taxi_Ctor_V((struct Taxi*)this->m_pt2);

	Minibus_Ctor_V(&this->m_m);
	Taxi_Ctor_V(&this->m_t);
}
 
void PublicConvoy_CCtor_PC(struct PublicConvoy *const this,
							const struct PublicConvoy *const other_)
{
	PublicTransport_Ctor_V(&this->m_publicTransport);
	this->m_publicTransport.m_vTable = (void(**)(struct PublicTransport*))vTable_PC;
	/* MIL */
	this->m_pt1 = (struct PublicTransport*)new(sizeof(struct Minibus));
	Minibus_CCtor_M((struct Minibus*)this->m_pt1, (struct Minibus*)other_->m_pt1);

	this->m_pt2 = (struct PublicTransport*)new(sizeof(struct Taxi));
	Taxi_CCtor_T((struct Taxi*)this->m_pt2, (struct Taxi*)other_->m_pt2);
	Minibus_CCtor_M(&this->m_m, &other_->m_m);
	Taxi_CCtor_T(&this->m_t, &other_->m_t);
}

void PublicConvoy_display_V(struct PublicConvoy *const this)
{
	this->m_pt1->m_vTable[1](this->m_pt1);
	this->m_pt2->m_vTable[1](this->m_pt2);

	Minibus_display_V(&this->m_m);
	Taxi_display_V(&this->m_t);
}

void PublicConvoy_Dtor_V(struct PublicConvoy *const this)
{
	this->m_publicTransport.m_vTable = (void(**)(struct PublicTransport*))vTable_PC;
	Taxi_Dtor_V((struct Taxi*)this->m_pt2);
	delete (this->m_pt2);
	Minibus_Dtor_V((struct Minibus*)this->m_pt1);
	delete (this->m_pt1);
	Taxi_Dtor_V(&this->m_t);
	Minibus_Dtor_V(&this->m_m);
	PublicTransport_Dtor_V(&this->m_publicTransport);
}

/**********************************Globals**************************************/
int max_func_T(const int *t1, const int *t2)
{
	return ((*t1 < *t2) ? *t1 : *t2);
}

void print_info_PT(struct PublicTransport *const a)
{
	a->m_vTable[1](a);
}

void print_info_v()
{
	PublicTransport_print_count_V();
}

void print_info_Minibus(struct Minibus *const m)
{
	(( void(*)(struct Minibus *const, int) )(m->m_PublicTransport.m_vTable)[2])(m, 3);
}

void print_info_int(int i, struct PublicTransport *out)
{
	struct Minibus ret = {0};
	Minibus_Ctor_V(&ret);

	printf("print_info(int i)\n");
	Minibus_display_V(&ret);
	
	PublicTransport_CCtor_PT(out, &(ret.m_PublicTransport));
	out->m_vTable = vTable_PT;

	Minibus_Dtor_V(&ret);
}

void taxi_display_T(struct Taxi *s)
{
	struct Taxi t = {0};
	Taxi_CCtor_T(&t, s);

	Taxi_display_V(&t);
	/* (t.m_PublicTransport.m_vTable[1])((struct PublicTransport*)&t); */
	Taxi_Dtor_V(&t);
}

/*******************************************Alocators**************************************/
void *new(size_t size)
{
	return malloc(size);
}

void *new_arr(size_t size)
{
	void *new_arr = malloc(size + sizeof(size_t));

	return (char*)new_arr + sizeof(size_t);
}

void delete(void *ptr_to_data)
{
	free(ptr_to_data);
}

void delete_arr(void *ptr_to_data)
{
	free(ptr_to_data);
}

/***********************************App****************************************/
int main(void)
{
	struct Minibus m = {0};
	struct PublicTransport* array[3];

	union
	{
		int i;
		struct Minibus m_arr2;
		struct Taxi t_arr2;
		struct PublicTransport p_arr2;
		struct PublicTransport out;
	}tmp_vars;

	struct PublicTransport arr2[3] = {0};
	struct Minibus m2 = {0};
	struct Minibus arr3[4] = {0};
	struct Taxi *arr4 = NULL;
	struct SpecialTaxi st = {0};

	struct PublicConvoy *ts1 = {0};
	struct PublicConvoy *ts2;
	Minibus_Ctor_V(&m);
	print_info_Minibus(&m);
	print_info_int(3, &tmp_vars.out);
	PublicTransport_display_V(&tmp_vars.out);
	PublicTransport_Dtor_V(&tmp_vars.out);

	array[0] = (struct PublicTransport*)new(sizeof(struct Minibus*));
	Minibus_Ctor_V((struct Minibus*)(array[0]));
	array[1] = (struct PublicTransport*)new(sizeof(struct Taxi*));
	Taxi_Ctor_V((struct Taxi*)(array[1]));
	array[2] = (struct PublicTransport*)new(sizeof(struct Minibus*));
	Minibus_Ctor_V((struct Minibus*)(array[2]));
	/* display array loop*/
	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		array[tmp_vars.i]->m_vTable[1](array[tmp_vars.i]);
	}
	/* delete array loop*/
	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		array[tmp_vars.i]->m_vTable[0](array[tmp_vars.i]);

		delete(array[tmp_vars.i]);
	}

	Minibus_Ctor_V(&tmp_vars.m_arr2);
	PublicTransport_CCtor_PT(&arr2[0], (struct PublicTransport*)&tmp_vars.m_arr2);
	Minibus_Dtor_V(&tmp_vars.m_arr2);

	Taxi_Ctor_V(&tmp_vars.t_arr2);
	PublicTransport_CCtor_PT(&arr2[1], (struct PublicTransport*)&tmp_vars.t_arr2);
	Taxi_Dtor_V(&tmp_vars.t_arr2);

	PublicTransport_Ctor_V(&tmp_vars.p_arr2);
	arr2[2] = tmp_vars.p_arr2;

	/*display arr2 loop*/
	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		arr2[tmp_vars.i].m_vTable[1](&arr2[tmp_vars.i]);
	}
	print_info_PT(&arr2[0]);

	PublicTransport_print_count_V();
	Minibus_Ctor_V(&m2);
	PublicTransport_print_count_V();

	for (tmp_vars.i = 0; tmp_vars.i < 4; ++tmp_vars.i)
	{
		Minibus_Ctor_V(&arr3[tmp_vars.i]);
	}

	arr4 = (struct Taxi*)new_arr(sizeof(struct Taxi) * 4);
	for (tmp_vars.i = 0; tmp_vars.i < 4; ++tmp_vars.i)
	{
		Taxi_Ctor_V(&arr4[tmp_vars.i]);
	}

	for (tmp_vars.i = 4; tmp_vars.i > 0; --tmp_vars.i)
	{
		Taxi_Dtor_V(&arr4[tmp_vars.i - 1]);
	}

 	delete_arr((char*)arr4 - sizeof(size_t));

	printf("%d\n", 2);
	printf("%d\n", 2);

	SpecialTaxi_Ctor_V(&st);
	taxi_display_T((struct Taxi*)&st);

	/* Convoy */
	ts1 = (struct PublicConvoy*)new(sizeof(struct PublicConvoy));
	PublicConvoy_Ctor_V(ts1);
	ts2 = (struct PublicConvoy*)new(sizeof(struct PublicConvoy));
	PublicConvoy_CCtor_PC(ts2, ts1);
	PublicConvoy_display_V(ts1);
	PublicConvoy_display_V(ts2);
	PublicConvoy_Dtor_V(ts1);
	delete(ts1);
	PublicConvoy_display_V(ts2);
	PublicConvoy_Dtor_V(ts2);
	delete(ts2);
	/*arr3 Dtor */
	SpecialTaxi_Dtor_V(&st);
	for (tmp_vars.i = 4; tmp_vars.i > 0; --tmp_vars.i)
	{
		Minibus_Dtor_V(&arr3[tmp_vars.i - 1]);
	}

	Minibus_Dtor_V(&m2);
	for(tmp_vars.i = 3; tmp_vars.i > 0; --tmp_vars.i)
	{
		PublicTransport_Dtor_V(&arr2[tmp_vars.i] - 1);
	}

	Minibus_Dtor_V(&m);
	
	return 0;
}

