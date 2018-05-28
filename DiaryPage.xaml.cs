using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Media.Capture;
using Windows.Media.MediaProperties;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.Storage.Pickers;
using Windows.Storage.AccessCache;
using System.Text;
using Windows.Storage.FileProperties;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Core;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MyDiary
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class DiaryPage : Page
    {
        MediaCapture captureManager_record;
        MediaCapture captureManager_video;
        private string diary_text;
        // store the recording
        private InMemoryRandomAccessStream record_buffer;
        // store the video
        private InMemoryRandomAccessStream video_buffer;
        private bool StartRecording = false;
        private bool StartVideo = false;

        DiaryItemViewModel ViewModel = DiaryItemViewModel.CreatInstance();

        public DiaryPage()
        {
            record_buffer = new InMemoryRandomAccessStream();
            video_buffer = new InMemoryRandomAccessStream();
            this.InitializeComponent();
        }
        private void Back(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }
        private void SaveDiary(object sender, RoutedEventArgs e)
        {
            diary_text = text.Text;
            SaveToFile(record_buffer, false);
            SaveToFile(video_buffer, true);
        }
        public async void Record(object sender, RoutedEventArgs e)
        {
            // begin recording
            if(StartRecording == false)
            {
                //await Initialize();
                //await DeleteExistingFile();
                if(record_buffer != null)
                    record_buffer.Dispose();
                record_buffer = new InMemoryRandomAccessStream();
                MediaCaptureInitializationSettings settings =
                  new MediaCaptureInitializationSettings
                  {
                      StreamingCaptureMode = StreamingCaptureMode.Audio
                  };
                captureManager_record = new MediaCapture();
                await captureManager_record.InitializeAsync(settings);
                await captureManager_record.StartRecordToStreamAsync(
                  MediaEncodingProfile.CreateMp3(AudioEncodingQuality.Auto), record_buffer);
                StartRecording = true;
            }
            // stop recording
            else
            {
                await captureManager_record.StopRecordAsync();
                //SaveAudioToFile();
                //SaveToFile(record_buffer, false);
                StartRecording = false;
            }
        }


        private async void SaveToFile(InMemoryRandomAccessStream _memoryBuffer, bool isVideo)
        {
            IRandomAccessStream audioStream = _memoryBuffer.CloneStream();
            StorageFolder storageFolder = Package.Current.InstalledLocation;
            string DEFAULT_AUDIO_FILENAME = "";
            int index = ViewModel.AllItems.Count;

            if (isVideo)
            {
                DEFAULT_AUDIO_FILENAME = index + ".mp3";
            }
            else
            {
                DEFAULT_AUDIO_FILENAME = index + ".mp4";
            }
    
            StorageFile storageFile = await storageFolder.CreateFileAsync(
              DEFAULT_AUDIO_FILENAME, CreationCollisionOption.GenerateUniqueName);

            using (IRandomAccessStream fileStream =
              await storageFile.OpenAsync(FileAccessMode.ReadWrite))
            {
                await RandomAccessStream.CopyAndCloseAsync(
                  audioStream.GetInputStreamAt(0), fileStream.GetOutputStreamAt(0));
                await audioStream.FlushAsync();
                audioStream.Dispose();
            }
        }

        public async Task PlayFromDisk()
        {
            await Window.Current.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                StorageFolder storageFolder = Package.Current.InstalledLocation;
                StorageFile storageFile = await storageFolder.GetFileAsync("1.mp4"); //"1.mp4"是从磁盘里读出来的文件的名
                IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.Read);
                showVideo.SetSource(stream, storageFile.FileType);
                showVideo.Play();
            });
        }

        // play the record from the 
        public void PlayRecord(object sender, RoutedEventArgs e)
        {
            MediaElement playbackMediaElement = new MediaElement();
            playbackMediaElement.SetSource(record_buffer, "MP3");
            playbackMediaElement.Play();
        }

        // play the video from the 
        public async void PlayVideo(object sender, RoutedEventArgs e)
        {
            capturePreview.Visibility = Visibility.Collapsed;
            showVideo.Visibility = Visibility.Visible;
            
            //await PlayFromDisk();
            //MediaElement playbackMediaElement = new MediaElement();
            showVideo.SetSource(video_buffer, "MP4");
            showVideo.Play();
            //capturePreview
        }

        async private void openCamera(object sender, RoutedEventArgs e)
        {
            if(StartVideo == false)
            {
                if (video_buffer != null)
                    video_buffer.Dispose();
                video_buffer = new InMemoryRandomAccessStream();
                showVideo.Visibility = Visibility.Collapsed;
                capturePreview.Visibility = Visibility.Visible;
                //ProfilePic.Visibility = Visibility.Collapsed;
                captureManager_video = new MediaCapture();
                //选择后置摄像头
                var cameraDevice = await FindCameraDeviceByPanelAsync(Windows.Devices.Enumeration.Panel.Back);
                if (cameraDevice == null)
                {
                    System.Diagnostics.Debug.WriteLine("No camera device found!");
                    return;
                }
                var settings = new MediaCaptureInitializationSettings
                {
                    StreamingCaptureMode = StreamingCaptureMode.Video,
                    //MediaCategory = MediaCategory.Other,
                    //AudioProcessing = AudioProcessing.Default,
                    //PhotoCaptureSource = PhotoCaptureSource.Photo,
                    AudioDeviceId = string.Empty,
                    VideoDeviceId = cameraDevice.Id
                };
                await captureManager_video.InitializeAsync(settings);
                //摄像头旋转90度
                //captureManager.SetPreviewRotation(VideoRotation.Clockwise90Degrees);
                capturePreview.Source = captureManager_video;
                // await captureManager_video.StartRecordToStreamAsync(MediaEncodingProfile.CreateMp3(AudioEncodingQuality.Auto), video_buffer);
                await captureManager_video.StartRecordToStreamAsync(MediaEncodingProfile.CreateMp4(VideoEncodingQuality.Auto), video_buffer);
                await captureManager_video.StartPreviewAsync();
                //await captureManager_video.StartPreviewAsync();
                StartVideo = true;
            }
            else
            {
                await captureManager_video.StopRecordAsync();
                //SavaVideoToFile();
                //SaveToFile(video_buffer, false);
                StartVideo = false;
            }
        }
        private static async Task<DeviceInformation> FindCameraDeviceByPanelAsync(Windows.Devices.Enumeration.Panel desired)
        {
            var allVideoDevices = await DeviceInformation.FindAllAsync(DeviceClass.VideoCapture);
            DeviceInformation desiredDevice = allVideoDevices.FirstOrDefault(x => x.EnclosureLocation != null && x.EnclosureLocation.Panel == desired);
            return desiredDevice ?? allVideoDevices.FirstOrDefault();

        }
    }
}
