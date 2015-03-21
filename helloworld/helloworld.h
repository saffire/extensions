#ifndef __MODULE_HELLOWORLD_H__
#define __MODULE_HELLOWORLD_H__

    typedef struct {
        // define here the extra data you need to use internally
    } t_helloworld_object_data;

    typedef struct {
        SAFFIRE_OBJECT_HEADER
        t_helloworld_object_data data;
        SAFFIRE_OBJECT_FOOTER
    } t_helloworld_object;

    t_helloworld_object Object_HelloWorld_struct;

    #define Object_HelloWorld   (t_object *)&Object_HelloWorld_struct

    t_module module_helloworld;

#endif
