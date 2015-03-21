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

#include "exif.h"

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
SAFFIRE_MODULE_METHOD(exif, ctor) {
    t_string_object *path_obj;

    if (! object_parse_arguments(SAFFIRE_METHOD_ARGS, "s",  &path_obj)) {
        return NULL;
    }

    t_exif_object *exif_obj = (t_exif_object *)self;

    exif_obj->data.ed = exif_data_new_from_file(OBJ2STR0(path_obj));

    if (! exif_obj->data.ed) {
        // Throw exception
        object_raise_exception(Object_FileNotFoundException, 1, "Cannot load exif data");
        return NULL;
    }

//    exif_data_foreach_content(ed, (void *)foreach_content, NULL);
    RETURN_SELF;
}

/**
 *
 */
SAFFIRE_MODULE_METHOD(exif, data) {
    t_exif_object *exif_obj = (t_exif_object *)self;

    // Return cached hash object
    if (exif_obj->data.hash_obj != NULL) {
        return (t_object *)exif_obj->data.hash_obj;
    }

    RETURN_STRING("Not implemented yet");
}

SAFFIRE_MODULE_METHOD(exif, getTagName) {
    t_numerical_object *tag_obj;

    if (! object_parse_arguments(SAFFIRE_METHOD_ARGS, "n",  &tag_obj)) {
        return NULL;
    }

    long tag = OBJ2NUM(tag_obj);
    ;

    RETURN_STRING_FROM_CHAR((const char *)exif_tag_get_name(tag));
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
    t_exif_object *exif_obj = (t_exif_object *)obj;
    if (exif_obj->data.ed) exif_free(exif_obj->data.ed);
    if (exif_obj->data.hash_obj) object_release((t_object *)exif_obj->data.hash_obj);
}


static void obj_destroy(t_object *obj) {
    smm_free(obj);
}


// Exif object management functions
t_object_funcs exif_funcs = {
        NULL,                 // Populate a exif object
        obj_free,             // Free a exif object
        obj_destroy,          // Destroy a exif object
        NULL,                 // Clone
        NULL,                 // Object cache
        NULL,                 // Hash
        NULL,                 // Cache
};



static void _obj_exif_init(void) {
    Object_Exif_struct.attributes = ht_create();

    object_add_internal_method((t_object *)&Object_Exif_struct, "__ctor",  ATTRIB_METHOD_CTOR, ATTRIB_VISIBILITY_PUBLIC, module_exif_method_ctor);
    object_add_internal_method((t_object *)&Object_Exif_struct, "dump",    ATTRIB_METHOD_NONE, ATTRIB_VISIBILITY_PUBLIC, module_exif_method_data);
    object_add_internal_method((t_object *)&Object_Exif_struct, "getTagName",    ATTRIB_METHOD_NONE, ATTRIB_VISIBILITY_PUBLIC, module_exif_method_getTagName);
}

static void _obj_exif_fini(void) {
    object_free_internal_object((t_object *)&Object_Exif_struct);
}


// Initial object
t_exif_object Object_Exif_struct = {
    OBJECT_HEAD_INIT("exif", objectTypeBase, OBJECT_TYPE_CLASS, &exif_funcs, sizeof(t_exif_object_data)),
    {
        NULL,       // Exif data
        NULL,       // Hash object
    },
    OBJECT_FOOTER
};





static t_object *_objects[] = {
    (t_object *)&Object_Exif_struct,
    NULL
};

t_module _saffire_module = {
    "::exif",
    "Exif module",
    _objects,
    _obj_exif_init,
    _obj_exif_fini,
};
