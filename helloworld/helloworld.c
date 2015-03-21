/*
 Copyright (c) 2012-2015, The Saffire Group
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the Saffire Group the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <string.h>
#include <saffire/modules/module_api.h>
#include <saffire/objects/objects.h>

#include "helloworld.h"

/* ======================================================================
 *   Supporting functions
 * ======================================================================
 */

/* ======================================================================
 *   Object methods
 * ======================================================================
 */

/**
 *
 */
SAFFIRE_MODULE_METHOD(helloworld, ctor) {
    t_helloworld_object *helloworld_obj = (t_helloworld_object *)self;

    // Initialize allocated data

    RETURN_SELF;
}

SAFFIRE_MODULE_METHOD(helloworld, hello) {
    t_string_object *target_obj;

    if (! object_parse_arguments(SAFFIRE_METHOD_ARGS, "s",  &target_obj)) {
        return NULL;
    }

    char *s = NULL;
    smm_asprintf_char(&s, "hello %s!", OBJ2STR0(target_obj));

    t_object *ret = STR02OBJ(s);

    smm_free(s);

    return ret;
}

/* ======================================================================
  *   Standard operators
  * ======================================================================
  */

/* ======================================================================
 *   Standard comparisons
 * ======================================================================
 */



/* ======================================================================
 *   Global object management functions and data
 * ======================================================================
 */

static void obj_free(t_object *obj) {
    t_helloworld_object *helloworld_obj = (t_helloworld_object *)obj;

    // Free allocated data if needed
}


static void obj_destroy(t_object *obj) {
    smm_free(obj);
}



// HelloWorld object management functions
t_object_funcs helloworld_funcs = {
        NULL,                 // Populate a helloworld object
        obj_free,             // Free a helloworld object
        obj_destroy,          // Destroy a helloworld object
        NULL,                 // Clone
        NULL,                 // Object cache
        NULL,                 // Hash
        NULL,                 // Cache
};



static void _obj_helloworld_init(void) {
    Object_HelloWorld_struct.attributes = ht_create();

    object_add_internal_method((t_object *)&Object_HelloWorld_struct, "__ctor",  ATTRIB_METHOD_CTOR, ATTRIB_VISIBILITY_PUBLIC, module_helloworld_method_ctor);
    object_add_internal_method((t_object *)&Object_HelloWorld_struct, "hello",   ATTRIB_METHOD_NONE, ATTRIB_VISIBILITY_PUBLIC, module_helloworld_method_hello);
}

static void _obj_helloworld_fini(void) {
    object_free_internal_object((t_object *)&Object_HelloWorld_struct);
}


// Initial object
t_helloworld_object Object_HelloWorld_struct = {
    OBJECT_HEAD_INIT("helloworld", objectTypeBase, OBJECT_TYPE_CLASS, &helloworld_funcs, sizeof(t_helloworld_object_data)),
    {
        // Initial data for helloworld objects
    },
    OBJECT_FOOTER
};





static t_object *_objects[] = {
    (t_object *)&Object_HelloWorld_struct,
    NULL
};

t_module _saffire_module = {
    "::example::helloworld",
    "Sample hello world saffire module",
    _objects,
    _obj_helloworld_init,
    _obj_helloworld_fini,
};
