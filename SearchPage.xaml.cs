using SQLitePCL;
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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MyDiary
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class SearchPage : Page
    {
        private string des;
        public SearchPage()
        {
            this.InitializeComponent();
        }
        private void Back(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }
        private void search(object sender, RoutedEventArgs e)
        {
            var db = App.conn;
            using (var statement = db.Prepare(App.SQL_SEARCH))
            {
                statement.Bind(1, st.Text);
                while (SQLiteResult.ROW == statement.Step())
                {
                    aa.Text = statement[1].ToString();
                }
            }
        }
    }
}
