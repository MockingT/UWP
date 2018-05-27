using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media;

namespace MyDiary
{
    public class DiaryItem
    {
        public DateTime date { get; set; }
        public string description { get; set; }
        public string text { get; set; }
        public string image_src { get; set; }
        private ImageSource ImgSource { get; set; }
    }
}
