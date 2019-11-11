/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>      /*     i / O    */
#include <stdlib.h>     /* malloc, free */


/****************structs Declaration*****************/
struct PublicTransport;
struct PublicTransport_VT;
struct Minibus;
struct Minibus_VT;
struct Taxi;
struct Taxi_VT;
struct SpecialTaxi;
struct SpecialTaxi_VT;

/***************PublicTransport methods****************/
void PublicTransport_C_V(struct PublicTransport *const this_);
void PublicTransport_D_V(struct PublicTransport *const this_);
void PublicTransport_C_PT(struct PublicTransport *const this_, const struct PublicTransport *const other_pt_);
void PublicTransport_display(struct PublicTransport *const this_);
void PublicTransport_print_count_V();
int PublicTransport_get_ID_PT(struct PublicTransport *const this_);

/*************************Minibus methods**********************************/
void Minibus_C_V(struct Minibus *const this_);
void Minibus_D_V(struct Minibus *const this_);
void Minibus_C_M(struct Minibus *const this_,
                  const struct Minibus *const other_);
void Minibus_display(struct Minibus *const this_);
void Minibus_wash(struct Minibus *const this_, int minutes_);

/*************************Taxi methods*************************************/
void Taxi_C_V(struct Taxi *const this_);
void Taxi_D_V(struct Taxi *const this_);
void Taxi_C_T(struct Taxi *const this_, const struct Taxi *const other_t_);
void Taxi_display(struct Taxi *const this_);

/*************************SpecialTaxi methods******************************/
void SpecialTaxi_C_V(struct SpecialTaxi *const this_);
void SpecialTaxi_C_ST(struct SpecialTaxi *const this_, const struct SpecialTaxi *const other_);
void SpecialTaxi_D_V(struct SpecialTaxi *const this_);
void SpecialTaxi_display(struct SpecialTaxi *const this_);

/*************************Global functions declaration*************************/
void print_info_PublicTransport(struct PublicTransport *const a_);
void printf_info_V();
void print_info_Minibus(struct Minibus *const m_);
void print_info_I(int i_, struct PublicTransport *out_);
void taxi_display_T(struct Taxi *s);

/*************************Structs******************************************************/

struct PublicTransport_VT
{
    void (*D_V)(struct PublicTransport *const this_);
    void (*display)(struct PublicTransport *const this_);
};

struct PublicTransport
{
    struct PublicTransport_VT *m_vt;
    int m_license_plate;
};
/**************************************************************************************/

struct Minibus_VT
{
    void (*D_V)(struct Minibus *const this_);
    void (*display)(struct Minibus *const this_);
    void (*wash)(struct Minibus *const this_, int minutes_);
};

struct Minibus
{
    struct PublicTransport m_publicTransport;
    int m_numSeats;
};
/**************************************************************************************/

struct Taxi_VT
{
    void (*D_V)(struct Taxi *const this_);
    void (*display)(struct Taxi *const this_);
};

struct Taxi
{
    struct PublicTransport m_publicTransport;
};
/**************************************************************************************/
struct SpecialTaxi_VT
{
    void (*D_V)(struct SpecialTaxi *const this_);
    void (*display)(struct SpecialTaxi *const this_);
};

struct SpecialTaxi
{
    struct Taxi m_Taxi;
};

/*********************************Global and static*************************************/
struct PublicTransport_VT g_PublicTransport_VT = {PublicTransport_D_V,
                                                  PublicTransport_display};

struct Minibus_VT g_Minibus_VT                 = {Minibus_D_V,
                                                  Minibus_display,
                                                  Minibus_wash};

struct Taxi_VT g_Taxi_VT                       = {Taxi_D_V,
                                                  Taxi_display};

struct SpecialTaxi_VT g_SpecialTaxi_VT         = {SpecialTaxi_D_V,
                                                  SpecialTaxi_display};

int PublicTransport_s_count = 0;

/************************Public Transportation implementation***************************/
void PublicTransport_C_V(struct PublicTransport *const this_)
{
    this_->m_vt = &g_PublicTransport_VT;
    /* MIL */
    this_->m_license_plate = ++PublicTransport_s_count;

    printf("PublicTransport::Ctor()%d\n", this_->m_license_plate);
}

void PublicTransport_D_V(struct PublicTransport *const this_)
{
    --PublicTransport_s_count;
    printf("PublicTransport::Dtor()%d\n", this_->m_license_plate);
}

void PublicTransport_C_PT(struct PublicTransport *const this_,
                          const struct PublicTransport *const other_)
{
	this_->m_vt = &g_PublicTransport_VT;
    /* MIL */
    this_->m_license_plate = ++PublicTransport_s_count;

    printf("PublicTransport::CCtor() %d\n", this_->m_license_plate);
}

void PublicTransport_display(struct PublicTransport *const this_)
{
    printf("PublicTransport::display(): %d\n", this_->m_license_plate);
}

void PublicTransport_print_count_V()
{
    printf("s_count: %d\n", PublicTransport_s_count);
}

int PublicTransport_get_ID_PT(struct PublicTransport *const this_)
{
    return this_->m_license_plate;
}

/***********************************Minibus implementation***********************************/
void Minibus_C_V(struct Minibus *const this_)
{
    /* MIL */
    PublicTransport_C_V(&this_->m_publicTransport);
    this_->m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_Minibus_VT;
    this_->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void Minibus_D_V(struct Minibus *const this_)
{
    printf("Minibus::Dtor()\n");
    PublicTransport_D_V(&this_->m_publicTransport);
}

void Minibus_C_M(struct Minibus *const this_, const struct Minibus *const other_m_)
{
    /*  MIL */
	PublicTransport_C_PT(&this_->m_publicTransport, &other_m_->m_publicTransport);  
  	this_->m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_Minibus_VT;
    this_->m_numSeats = other_m_->m_numSeats;

    printf("Minibus::CCtor()\n");
}

void Minibus_display(struct Minibus *const this_)
{
    printf("Minibus::display() ID:%d", PublicTransport_get_ID_PT(&(this_->m_publicTransport)));
    printf(" num seats:%d\n", this_->m_numSeats);
}

void Minibus_wash(struct Minibus *const this_, int minutes_)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes_, 
                                        PublicTransport_get_ID_PT(&(this_->m_publicTransport)));
}

/***********************************Taxi implementation*************************************/
void Taxi_C_V(struct Taxi *const this_)
{
    /*  MIL */
    PublicTransport_C_V(&this_->m_publicTransport);
    this_->m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_Taxi_VT;

    printf("Taxi::Ctor()\n");
}

void Taxi_D_V(struct Taxi *const this_)
{
    printf("Taxi::Dtor()\n");
    PublicTransport_D_V(&this_->m_publicTransport);
}

void Taxi_C_T(struct Taxi *const this_, const struct Taxi *const other_t_)
{
    /*  MIL */
	PublicTransport_C_PT(&this_->m_publicTransport, &other_t_->m_publicTransport);
	this_->m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_Taxi_VT;
    printf("Taxi::CCtor()\n");    
}

void Taxi_display(struct Taxi *const this_)
{
    printf("Taxi::display() ID:%d\n", PublicTransport_get_ID_PT(&(this_->m_publicTransport)));
}

/*************************SpecialTaxi implementation********************************/
void SpecialTaxi_C_V(struct SpecialTaxi *const this_)
{
    /*  MIL */
    Taxi_C_V(&this_->m_Taxi);
    this_->m_Taxi.m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_SpecialTaxi_VT;

    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_C_ST(struct SpecialTaxi *const this_, const struct SpecialTaxi *const other_) 
{
    /*  MIL */
    PublicTransport_C_PT((struct PublicTransport*)&this_, &other_->m_Taxi.m_publicTransport);
	this_->m_Taxi.m_publicTransport.m_vt = (struct PublicTransport_VT*)&g_SpecialTaxi_VT;

    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi_D_V(struct SpecialTaxi *const this_)
{
    printf("SpecialTaxi::Dtor()\n");

    Taxi_D_V(&this_->m_Taxi);
}

void SpecialTaxi_display(struct SpecialTaxi *const this_)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransport_get_ID_PT(&(this_->m_Taxi.m_publicTransport)));
}


/********************Global functions implementation*********************/

void print_info_PublicTransport(struct PublicTransport *const a_)
{
	a_->m_vt->display(a_);
}

void print_info_Minibus(struct Minibus *const m_)
{
    ((struct Minibus_VT*)m_->m_publicTransport.m_vt)->wash(m_, 3);
}

void print_info_I(int i_, struct PublicTransport *out_)
{
    struct Minibus ret = {0};
    
    Minibus_C_V(&ret);

    printf("print_info(int i)\n");
    ((struct Minibus_VT*)ret.m_publicTransport.m_vt)->display(&ret);

    PublicTransport_C_PT(out_, &(ret.m_publicTransport));
    out_->m_vt = &g_PublicTransport_VT;

    Minibus_D_V(&ret);
}

void taxi_display_T(struct Taxi *s)
{
	struct Taxi t = {0};
	Taxi_C_T(&t, s);
	
	((struct Taxi_VT *const)(t.m_publicTransport.m_vt))->display(&t);
	Taxi_D_V(&t);
}

/*******************************************Alocators**************************************/
void *new(size_t size)
{
	return malloc(size);
}

void *new_arr(size_t size, size_t num_of_elems)
{
	void *new_arr = malloc(size * num_of_elems + 8);
	*(size_t*)new_arr = num_of_elems;

	return (char*)new_arr + 8;
}

void delete(void *ptr_to_data)
{
	free(ptr_to_data);
}

void delete_arr(void *ptr_to_data)
{
	free((char*)ptr_to_data - 8);
}

/**********************************************Template*******************************************************/

int max_func(const int *t1, const int *t2)
{
	return (*t1 > *t2) ? *t1 : *t2;
}

/*************************************************MAIN********************************************************/
int main(void)
{
	struct Minibus m = {0};
	struct PublicTransport out = {0};
	struct PublicTransport *array[3] = {NULL};

	struct PublicTransport arr2[3] = {0};
	struct PublicTransport m_to_pt = {0};
	struct PublicTransport t_to_pt = {0};

	struct Minibus m_to_print = {0};

	struct Minibus arr3[4] = {0};
	struct Taxi *arr4 = NULL;

	struct SpecialTaxi st = {0};

	union 
	{
		int i;
		struct Minibus m_arr2;
		struct Taxi t_arr2;
		struct PublicTransport p_arr2;
	}tmp_vars;

	Minibus_C_V(&m);
	print_info_Minibus(&m);
	print_info_I(3, &out);
 	out.m_vt->display(&out);
	PublicTransport_D_V(&out);

	array[0] = (struct PublicTransport*)new(sizeof(struct Minibus));
	Minibus_C_V((struct Minibus *const)array[0]);

	array[1] = (struct PublicTransport*)new(sizeof(struct Taxi));
	Taxi_C_V((struct Taxi *const)array[1]);

	array[2] = (struct PublicTransport*)new(sizeof(struct Minibus));
	Minibus_C_V((struct Minibus *const)array[2]);

	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		array[tmp_vars.i]->m_vt->display(array[tmp_vars.i]);
	}

	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		array[tmp_vars.i]->m_vt->D_V(array[tmp_vars.i]);
		delete(array[tmp_vars.i]);
	}

	Minibus_C_V(&tmp_vars.m_arr2);

	PublicTransport_C_PT(&m_to_pt, (struct PublicTransport*)&tmp_vars.m_arr2);
	Minibus_D_V(&tmp_vars.m_arr2);
	arr2[0] = m_to_pt;
 
	Taxi_C_V(&tmp_vars.t_arr2);
	PublicTransport_C_PT(&t_to_pt, (struct PublicTransport*)&tmp_vars.t_arr2);
	arr2[1] = t_to_pt;
	Taxi_D_V(&tmp_vars.t_arr2);

	PublicTransport_C_V(&tmp_vars.p_arr2);
	arr2[2] = tmp_vars.p_arr2;

	for (tmp_vars.i = 0; tmp_vars.i < 3; ++tmp_vars.i)
	{
		arr2[tmp_vars.i].m_vt->display(&arr2[tmp_vars.i]);
	}

    print_info_PublicTransport(&arr2[0]);
	PublicTransport_print_count_V();
	Minibus_C_V(&m_to_print);
	PublicTransport_print_count_V();

	for (tmp_vars.i = 0; tmp_vars.i < 4; ++tmp_vars.i)
	{
		Minibus_C_V(&arr3[tmp_vars.i]);
	}
	
	arr4 = (struct Taxi*)new_arr((sizeof(struct Taxi)), 4);
	
	Taxi_C_V(&arr4[0]);
	Taxi_C_V(&arr4[1]);
	Taxi_C_V(&arr4[2]);
	Taxi_C_V(&arr4[3]);

	Taxi_D_V(&arr4[3]);
	Taxi_D_V(&arr4[2]);
	Taxi_D_V(&arr4[1]);
	Taxi_D_V(&arr4[0]);

	delete_arr(arr4);

	printf("%d\n", 2);
	printf("%d\n", 2);

	SpecialTaxi_C_V(&st);
	taxi_display_T(&st.m_Taxi);
	SpecialTaxi_D_V(&st);

	for (tmp_vars.i = 3; tmp_vars.i >= 0; --tmp_vars.i)
	{
		Minibus_D_V(&arr3[tmp_vars.i]);
	}

	Minibus_D_V(&m_to_print);
	
	for (tmp_vars.i = 2; tmp_vars.i >= 0; --tmp_vars.i)
	{
		PublicTransport_D_V(&arr2[tmp_vars.i]);
	}

	Minibus_D_V(&m);
	
	return 0;
}