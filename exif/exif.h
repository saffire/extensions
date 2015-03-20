#ifndef __MODULE_EXIF_H__
#define __MODULE_EXIF_H__

    #include <libexif/exif-data.h>

    typedef struct {
        t_hash_object *hash_obj;
        ExifData *ed;
    } t_exif_object_data;

    typedef struct {
        SAFFIRE_OBJECT_HEADER
        t_exif_object_data data;
        SAFFIRE_OBJECT_FOOTER
    } t_exif_object;

    t_exif_object Object_Exif_struct;

    #define Object_Exif   (t_object *)&Object_Exif_struct

    t_module module_exif;

#endif
