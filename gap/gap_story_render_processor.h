/* gap_story_render_processor.h
 *
 *  GAP storyboard rendering processor.
 *
 */

/*
 * 2006.06.25  hof  - created (moved stuff from the former gap_gve_story modules to this  new module)
 *
 */

/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef GAP_STORY_RENDER_PROCESSOR_H
#define GAP_STORY_RENDER_PROCESSOR_H

#include "libgimp/gimp.h"
#include "gap_vid_api.h"
#include "gap_story_file.h"
#include "gap_lib_common_defs.h"
#include "gap_story_render_types.h"

/* G_DIR_SEPARATOR (is defined in glib.h if you have glib-1.2.0 or later) */
#ifdef G_OS_WIN32

/* Filenames in WIN/DOS Style */
#ifndef G_DIR_SEPARATOR
#define G_DIR_SEPARATOR '\\'
#endif
#define DIR_ROOT ':'

#else  /* !G_OS_WIN32 */

/* Filenames in UNIX Style */
#ifndef G_DIR_SEPARATOR
#define G_DIR_SEPARATOR '/'
#endif
#define DIR_ROOT '/'

#endif /* !G_OS_WIN32 */



#define GAP_STB_RENDER_GVA_FRAMES_TO_KEEP_CACHED 36


#define GAP_VID_ENC_SAVE_MULTILAYER   "GAP_VID_ENC_SAVE_MULTILAYER"
#define GAP_VID_ENC_SAVE_FLAT         "GAP_VID_ENC_SAVE_FLAT"
#define GAP_VID_ENC_MONITOR           "GAP_VID_ENC_MONITOR"




/* --------------------------*/
/* PROCEDURE DECLARATIONS    */
/* --------------------------*/

void     gap_story_render_debug_print_framerange_list(GapStoryRenderFrameRangeElem *frn_list
                             , gint32 track                    /* -1 show all tracks */
                             );
void     gap_story_render_debug_print_audiorange_list(GapStoryRenderAudioRangeElem *aud_list
                             , gint32 track                    /* -1 show all tracks */
                             );


void     gap_story_render_drop_image_cache(void);

void     gap_story_render_remove_tmp_audiofiles(GapStoryRenderVidHandle *vidhand);
void     gap_story_render_drop_audio_cache(void);



gint32   gap_story_render_fetch_composite_image(GapStoryRenderVidHandle *vidhand
                    , gint32 master_frame_nr  /* starts at 1 */
                    , gint32  vid_width       /* desired Video Width in pixels */
                    , gint32  vid_height      /* desired Video Height in pixels */
                    , char *filtermacro_file  /* NULL if no filtermacro is used */
                    , gint32 *layer_id        /* output: Id of the only layer in the composite image */
                 );

gboolean gap_story_render_fetch_composite_image_or_chunk(GapStoryRenderVidHandle *vidhand
                    , gint32 master_frame_nr  /* starts at 1 */
                    , gint32  vid_width       /* desired Video Width in pixels */
                    , gint32  vid_height      /* desired Video Height in pixels */
                    , char *filtermacro_file  /* NULL if no filtermacro is used */
                    , gint32 *layer_id        /* output: Id of the only layer in the composite image */

                    , gint32 *image_id        /* output: Id of the only layer in the composite image */
                    , gboolean dont_recode_flag                /* IN: TRUE try to fetch comressed chunk if possible */
                    , char *vcodec_name                        /* IN: video_codec used in the calling encoder program */
                    , gboolean *force_keyframe                 /* OUT: the calling encoder should encode an I-Frame */
                    , unsigned char *video_frame_chunk_data    /* OUT: */
                    , gint32 *video_frame_chunk_size           /* OUT: */
                    , gint32 video_frame_chunk_maxsize         /* IN: */
                    , gdouble master_framerate
                    , gint32  max_master_frame_nr   /* the number of frames that will be encode in total */
                 );

GapStoryRenderVidHandle *  gap_story_render_open_vid_handle_from_stb(
                           GapStoryBoard *stb_ptr
                          ,gint32 *frame_count   /* output total frame_count , or 0 on failure */
                          );

GapStoryRenderVidHandle *  gap_story_render_open_vid_handle(
			   GapLibTypeInputRange input_mode
			  ,gint32 image_id 
                          ,const char *storyboard_file
                          ,const char *basename
                          ,const char *ext
                          ,gint32  frame_from
                          ,gint32  frame_to
                          ,gint32 *frame_count   /* output total frame_count , or 0 on failure */
                          );

GapStoryRenderVidHandle *  gap_story_render_open_extended_video_handle(
                           gboolean ignore_audio
                          ,gboolean igore_video
			  ,gboolean create_audio_tmp_files
                          ,gdouble  *progress_ptr
                          ,char *status_msg
                          ,gint32 status_msg_len
			  ,GapLibTypeInputRange input_mode
                          ,const char *imagename
                          ,const char *storyboard_file
                          ,const char *basename
                          ,const char *ext
                          ,gint32  frame_from
                          ,gint32  frame_to
                          ,gint32 *frame_count   /* output total frame_count , or 0 on failure */
                          );

void    gap_story_render_close_vid_handle(GapStoryRenderVidHandle *vidhand);
void    gap_story_render_set_audio_resampling_program(
                           GapStoryRenderVidHandle *vidhand
                           , char *util_sox
                           , char *util_sox_options
                           );
void      gap_story_render_set_stb_error(GapStoryRenderErrors *sterr, char *errtext);
void      gap_story_render_set_stb_warning(GapStoryRenderErrors *sterr, char *errtext);
void      gap_story_render_calc_audio_playtime(GapStoryRenderVidHandle *vidhand, gdouble *aud_total_sec);
gboolean  gap_story_render_create_composite_audiofile(GapStoryRenderVidHandle *vidhand
                            , char *comp_audiofile
                            );

#endif        /* GAP_STORY_RENDER_PROCESSOR_H */