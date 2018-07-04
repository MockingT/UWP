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
using Windows.Graphics.Imaging;
using Windows.Graphics.Display;

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

        private InMemoryRandomAccessStream img_buffer;
        private bool StartRecording = false;
        private bool StartVideo = false;

        string recordFileName = "";
        string videoFileName = "";
        string imgFileName = "";

        DiaryItemViewModel ViewModel = DiaryItemViewModel.CreatInstance();


        public DiaryPage()
        {

            record_buffer = new InMemoryRandomAccessStream();
            video_buffer = new InMemoryRandomAccessStream();
            this.InitializeComponent();
            //initial();
            if (ViewModel.SelectedItem != null)
            {
                text.Text = ViewModel.SelectedItem.description;
                recordFileName = ViewModel.SelectedItem.record;
                videoFileName = ViewModel.SelectedItem.videoSrc;

            }
        }

        public void setDate()
        {
            int date = DateTime.Now.Day;
            topDate.Text = date.ToString();
            switch (DateTime.Now.Month)
            {
                case 1:
                    topDate.Text = "Jan";
                    break;
                case 2:
                    topDate.Text = "Feb";
                    break;
                case 3:
                    topDate.Text = "March";
                    break;
                case 4:
                    topDate.Text = "April";
                    break;
                case 5:
                    topDate.Text = "May";
                    break;
                case 6:
                    topDate.Text = "June";
                    break;
                case 7:
                    topDate.Text = "July";
                    break;
                case 8:
                    topDate.Text = "Aug";
                    break;
                case 9:
                    topDate.Text = "Sep";
                    break;
                case 10:
                    topDate.Text = "Oct";
                    break;
                case 11:
                    topDate.Text = "Nov";
                    break;
                case 12:
                    topDate.Text = "Dec";
                    break;
            }


        }

        private void initial()
        {
            ViewModel.AddNewDiary(DateTime.Now, "10129019", "", "");
        }

        private void Back(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }
        private void SaveDiary(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                text.Text = ViewModel.SelectedItem.description;
                recordFileName = ViewModel.SelectedItem.record;
                videoFileName = ViewModel.SelectedItem.videoSrc;

            }
            else
            {

                diary_text = text.Text;
                SaveToFile(record_buffer, false);
                SaveToFile(video_buffer, true);
                
                var db = App.conn;
                using (var item = db.Prepare(App.SQL_INSERT))
                {
                    item.Bind(1, ViewModel.AllItems.Count);
                    item.Bind(2, diary_text);
                    item.Bind(3, DateTime.Now.ToString());
                    item.Bind(4, recordFileName);
                    item.Bind(5, videoFileName);
                    item.Step();
                }
                ViewModel.AddNewDiary(DateTime.Now, diary_text, recordFileName, videoFileName);

                Frame.Navigate(typeof(MainPage));
            }

        }

        private void DeleteDiary(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                var db = App.conn;
                using (var item = db.Prepare(App.SQL_DELETE))
                {
                    item.Bind(1, ViewModel.SelectedItem.date.ToString());
                    item.Step();
                }
                ViewModel.DelteDiary();
                Frame.Navigate(typeof(MainPage));
            }
            else
            {
            }

        }

        public async void Record(object sender, RoutedEventArgs e)
        {
            // begin recording
            if (StartRecording == false)
            {
                //await Initialize();
                //await DeleteExistingFile();
                if (record_buffer != null)
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

        /*
         * 位于项目的 \bin\x86\Debug 目录中
         * 
         * */
        private async void SaveToFile(InMemoryRandomAccessStream _memoryBuffer, bool isVideo)
        {
            IRandomAccessStream audioStream = _memoryBuffer.CloneStream();
            StorageFolder storageFolder = Package.Current.InstalledLocation;
            string DEFAULT_AUDIO_FILENAME = "";


            if (isVideo)
            {
                recordFileName = DateTime.Now.Year.ToString();
                recordFileName += DateTime.Now.Month.ToString();
                recordFileName += DateTime.Now.Day.ToString();

                DEFAULT_AUDIO_FILENAME = recordFileName + ".mp3";
            }
            else
            {
                videoFileName = DateTime.Now.Year.ToString();
                videoFileName += DateTime.Now.Month.ToString();
                videoFileName += DateTime.Now.Day.ToString();

                DEFAULT_AUDIO_FILENAME = videoFileName + ".mp4";
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

        public async Task PlayFromDisk(int type)
        {
            if (type == 0)
            {
                recordFileName = ViewModel.SelectedItem.record;
                recordFileName += ".mp3";
                await Window.Current.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
                {
                    StorageFolder storageFolder = Package.Current.InstalledLocation;
                    StorageFile storageFile = await storageFolder.GetFileAsync(recordFileName); //"1.mp3"是从磁盘里读出来的文件的名
                    IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.Read);
                    showVideo.SetSource(stream, storageFile.FileType);
                    showVideo.Play();
                });
            }
            else if(type == 1)
            {
                videoFileName = ViewModel.SelectedItem.videoSrc;
                videoFileName += ".mp4";
                await Window.Current.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
                {
                    StorageFolder storageFolder = Package.Current.InstalledLocation;
                    StorageFile storageFile = await storageFolder.GetFileAsync(videoFileName); //"1.mp4"是从磁盘里读出来的文件的名
                    IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.Read);
                    showVideo.SetSource(stream, storageFile.FileType);
                    showVideo.Play();
                });
            }
        }

        // play the record from the 
        public async void PlayRecord(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                await PlayFromDisk(0);
                return;
            }
            MediaElement playbackMediaElement = new MediaElement();
            playbackMediaElement.SetSource(record_buffer, "MP3");
            playbackMediaElement.Play();
        }

        // play the video from the 
        public async void PlayVideo(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                await PlayFromDisk(1);
                return;
            }
            capturePreview.Visibility = Visibility.Collapsed;
            showVideo.Visibility = Visibility.Visible;
            
            //MediaElement playbackMediaElement = new MediaElement();
            showVideo.SetSource(video_buffer, "MP4");
            showVideo.Play();
            //capturePreview
        }

        async private void openCamera(object sender, RoutedEventArgs e)
        {
            if (StartVideo == false)
            {
                //camera.Icon = IconElement.
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
                SaveToFile(video_buffer, false);
                StartVideo = false;
            }
        }
        private static async Task<DeviceInformation> FindCameraDeviceByPanelAsync(Windows.Devices.Enumeration.Panel desired)
        {
            var allVideoDevices = await DeviceInformation.FindAllAsync(DeviceClass.VideoCapture);
            DeviceInformation desiredDevice = allVideoDevices.FirstOrDefault(x => x.EnclosureLocation != null && x.EnclosureLocation.Panel == desired);
            return desiredDevice ?? allVideoDevices.FirstOrDefault();

        }
        /*
        private async void image_Tapped(object sender, TappedRoutedEventArgs e)
        {

            if (img_buffer != null)
            {
                img_buffer.Dispose();
            }

            FileOpenPicker fop = new FileOpenPicker();

            fop.ViewMode = PickerViewMode.Thumbnail;
            //设置打开时的默认路径，这里选择的是图片库
            fop.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            fop.FileTypeFilter.Add(".jpg");
            fop.FileTypeFilter.Add(".png");
            fop.FileTypeFilter.Add(".jpeg");
            fop.FileTypeFilter.Add(".bmp");
            fop.FileTypeFilter.Add(".gif");
            StorageFile file = await fop.PickSingleFileAsync();

            BitmapImage srcImage = new BitmapImage();
            //title.Text = file.Path;
            if (file != null)
            {

                using (IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read))
                {
                    await srcImage.SetSourceAsync(stream);
                    image.Source = srcImage;

                }
            }
        }*/
    }
}