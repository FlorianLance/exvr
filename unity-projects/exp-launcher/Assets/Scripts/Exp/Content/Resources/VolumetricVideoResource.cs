
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

// unity
using UnityEngine;

namespace Ex {

    namespace DLL {

        public class VolumetricVideoResource : CppDllImport {

            //private float[] jointsPositions = new float[Kinect2.nbJoints * 3];
            //private float[] jointsEulerRotations = new float[Kinect2.nbJoints * 3];
            //private int[] jointsStates = new int[Kinect2.nbJoints];

            public VolumetricVideoResource() : base() {
            }

            public bool load(string path) {
                return load_volumetric_video_resource(_handle, path) == 1;
            }

            public int nb_cameras() {
                return get_cameras_nb_volumetric_video_resource(_handle);
            }

            public int nb_frames(int idCamera) {
                return get_nb_frames_volumetric_video_resource(_handle, idCamera);
            }

            public float duration_ms(int idCamera) {
                return get_duration_ms_volumetric_video_resource(_handle, idCamera);
            }

            public Matrix4x4 model(int idCamera) {

                float[] t = new float[16];
                get_camera_transform_volumetric_video_resource(_handle, idCamera, t);
                return new Matrix4x4(new Vector4(t[0], t[1], t[2], 0),     // c0
                                     new Vector4(t[4], t[5], t[6], 0),     // c1
                                     new Vector4(t[8], t[9], t[10], 0),    // c2
                                     new Vector4(t[12], t[13], t[14], 1)); // c3
            }

            public int id_frame_from_time(int idCamera, float timeMs) {
                return get_id_frame_from_time_ms_volumetric_video_resource(_handle, idCamera, timeMs);
            }

            public int uncompress_frame(int idCamera, int idFrame) {
                return uncompress_frame_volumetric_video_resource(_handle, idCamera, idFrame);
            }

            public void copy_uncompressed_data(int idCamera, IntPtr vertices, IntPtr colors) {
                copy_uncompressed_data_volumetric_video_resource(_handle, idCamera, vertices, colors);
            }

            public void process_audio() {
                process_audio_volumetric_video_resource(_handle);
            }
   
            public int audio_channel_samples_size(int idCamera, int idChannel) {
                return get_audio_channel_size_volumetric_video_resource(_handle, idCamera, idChannel);
            }
            public void copy_audio_samples(int idCamera, int idChannel, IntPtr audioSamples) {
                copy_audio_samples_volumetric_video_resource(_handle, idCamera, idChannel, audioSamples);
            }


            #region memory_management

            protected override void create_DLL_class() {
                _handle = new HandleRef(this, create_volumetric_video_resource());
            }

            protected override void delete_DLL_class() {
                delete_volumetric_video_resource(_handle);
            }


            #endregion memory_management    
            #region DllImport

            // memory management
            [DllImport("lnco-exvr-export", EntryPoint = "create_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern IntPtr create_volumetric_video_resource();

            [DllImport("lnco-exvr-export", EntryPoint = "delete_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern void delete_volumetric_video_resource(HandleRef volumetricVideoResource);

            [DllImport("lnco-exvr-export", EntryPoint = "load_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int load_volumetric_video_resource(HandleRef volumetricVideoResource, string pathResource);

            [DllImport("lnco-exvr-export", EntryPoint = "get_cameras_nb_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int get_cameras_nb_volumetric_video_resource(HandleRef volumetricVideoResource);

            [DllImport("lnco-exvr-export", EntryPoint = "get_nb_frames_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int get_nb_frames_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera);

            [DllImport("lnco-exvr-export", EntryPoint = "get_duration_ms_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern float get_duration_ms_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera);

            [DllImport("lnco-exvr-export", EntryPoint = "get_camera_transform_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern void get_camera_transform_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, float[] model);


            [DllImport("lnco-exvr-export", EntryPoint = "get_id_frame_from_time_ms_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int get_id_frame_from_time_ms_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, float timeMs);

            [DllImport("lnco-exvr-export", EntryPoint = "uncompress_frame_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int uncompress_frame_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, int idFrame);

            [DllImport("lnco-exvr-export", EntryPoint = "copy_uncompressed_data_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern void copy_uncompressed_data_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, IntPtr vertices, IntPtr colors);

            [DllImport("lnco-exvr-export", EntryPoint = "process_audio_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern void process_audio_volumetric_video_resource(HandleRef volumetricVideoResource);

            [DllImport("lnco-exvr-export", EntryPoint = "get_audio_channel_size_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern int get_audio_channel_size_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, int idChannel);

            [DllImport("lnco-exvr-export", EntryPoint = "copy_audio_samples_volumetric_video_resource", CallingConvention = CallingConvention.Cdecl)]
            static private extern void copy_audio_samples_volumetric_video_resource(HandleRef volumetricVideoResource, int idCamera, int idChannel, IntPtr audioSamples);


            #endregion DllImport        
        }
    }

    public class VolumetricVideoResource : ResourceFile {

        public DLL.VolumetricVideoResource video = null;

        public VolumetricVideoResource(int key, string alias, string path) : base(key, alias, path) {
            video = new DLL.VolumetricVideoResource();
            if (!video.load(path)) {
                log_error(string.Format("Cannot load volumetric video from path {0}.", path));
            }
        }

        public override void clean() {
            video.Dispose();
        }
    }
}