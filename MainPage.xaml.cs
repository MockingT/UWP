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
            this.ViewModel = App.ViewModel;
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
    }
}
