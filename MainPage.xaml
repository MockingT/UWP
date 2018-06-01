using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Text;
using Windows.Data.Json;
using Windows.ApplicationModel.DataTransfer;
using Windows.ApplicationModel;
using Windows.Storage.Streams;


// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace MyDiary
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private DiaryItemViewModel ViewModel { get; set; }
        public MainPage()
        {
            this.InitializeComponent();
            setDate();
            this.ViewModel = App.ViewModel;
            GetNews();
        }
        //set the date on the top of the main page
        public void setDate()
        {
            int date = DateTime.Now.Day;
            top_date.Text = date.ToString();
            switch (DateTime.Now.Month)
            {
                case 1:
                    top_month.Text = "Jan";
                    break;
                case 2:
                    top_month.Text = "Feb";
                    break;
                case 3:
                    top_month.Text = "March";
                    break;
                case 4:
                    top_month.Text = "April";
                    break;
                case 5:
                    top_month.Text = "May";
                    break;
                case 6:
                    top_month.Text = "June";
                    break;
                case 7:
                    top_month.Text = "July";
                    break;
                case 8:
                    top_month.Text = "Aug";
                    break;
                case 9:
                    top_month.Text = "Sep";
                    break;
                case 10:
                    top_month.Text = "Oct";
                    break;
                case 11:
                    top_month.Text = "Nov";
                    break;
                case 12:
                    top_month.Text = "Dec";
                    break;
            }


        }

        private void ToDiaryPage(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(DiaryPage));
        }
        private void ToSearchPage(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(SearchPage));
        }
        private void ToCalenderPage(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(CalenderPage));
        }
        private async void GetNews()
        {
            //Create an HTTP client object
            Windows.Web.Http.HttpClient httpClient = new Windows.Web.Http.HttpClient();

            //Add a user-agent header to the GET request. 
            var headers = httpClient.DefaultRequestHeaders;

            //The safe way to add a header value is to use the TryParseAdd method and verify the return value is true,
            //especially if the header value is coming from user input.
            string header = "ie";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }


            header = "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }
            String api = "http://api.avatardata.cn/TouTiao/Query";
            String appkey = "2d408009841f439b864c3c00a3c0bdbe";
            NewsBlock.Text = "正在加载新闻";
            StringBuilder uriBuilder = new StringBuilder();
            uriBuilder.Append(api).Append("?key=").Append(appkey).Append("&type=top");

            //var i = new Windows.UI.Popups.MessageDialog(uriBuilder.ToString()).ShowAsync();

            Uri requestUri = new Uri(uriBuilder.ToString());
            //Send the GET request asynchronously and retrieve the response as a string.

            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";

            try
            {
                //Send the GET request
                httpResponse = await httpClient.GetAsync(requestUri);
                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();
                //NewsBlock.Text = httpResponseBody;
                //用string初始化JsonObject
                JsonObject jsonObject = JsonObject.Parse(httpResponseBody);

                // JsonArray arr = jsonObject.GetNamedArray("result").GetArray();
                JsonObject obj = jsonObject.GetNamedObject("result");
                JsonArray arr = obj.GetNamedArray("data").GetArray();
                
                StringBuilder s = new StringBuilder();
                s.Append(arr[0].GetObject().GetNamedValue("title").GetString());
                s.Append("。\n新闻来源于");
                s.Append(arr[0].GetObject().GetNamedValue("url").GetString());
                
                NewsBlock.Text = s.ToString();
                

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
        }

        private void Share(object sender, RoutedEventArgs e)
        {
            DataTransferManager dataTransferManager = DataTransferManager.GetForCurrentView();
            dataTransferManager.DataRequested += DataTransferManager_DataRequested;
            DataTransferManager.ShowShareUI();
        }

        async void DataTransferManager_DataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            DataRequest request = args.Request;
            //DiaryItem item = ViewModel.SelectedItem;
            DiaryItem item = new DiaryItem();
            if(item != null)
            {
                request.Data.Properties.Title = "Diary";

                //request.Data.Properties.Description = item.description;
                request.Data.Properties.Description = "haha";
                request.Data.SetText("Diary");
                request.Data.SetText("haha");
                // request.Data.SetText(item.description);

                var Deferral = args.Request.GetDeferral();
                var SharePhoto = await Package.Current.InstalledLocation.GetFileAsync("Assets\\pic.jpg");
                request.Data.Properties.Thumbnail = RandomAccessStreamReference.CreateFromFile(SharePhoto);
                request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(SharePhoto));
                Deferral.Complete();
            }
            

        }

    }
}
