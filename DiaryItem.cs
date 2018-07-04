using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace MyDiary
{
    /*
     * store the item in the viewModel, every item has the info below:
     * id - 
     * date
     * desciption
     * imageSorce
     * VideoSrc
     * 
     * 
     * */
    public class DiaryItem : INotifyPropertyChanged
    {
        public string id { get; set; }

        public DateTimeOffset date { get; set; }
        public string year;
        public string month;
        public string day;
        public string weekday;

        private string des;
        public string description {
            get { return this.des; }
            set
            {
                this.des = value;
                this.OnPropertyChanged();
            }
        }

 
        private string Record;
        public string record
        {
            get { return this.Record; }
            set
            {
                this.Record = value;
                this.OnPropertyChanged();
            }
        }

        private string VideoSrc;
        public string videoSrc
        {
            get { return this.VideoSrc; }
            set
            {
                this.VideoSrc = value;
                this.OnPropertyChanged();
            }
        }

        public DiaryItem(DateTimeOffset date, string des, string record, string videoSrc)
        {
            this.id = Guid.NewGuid().ToString(); // create new id
            this.description = des;
            this.date = date;
            year = date.Year.ToString();
            month = date.Month.ToString();
            day = date.Day.ToString();
            weekday = date.DayOfWeek.ToString();
            this.Record = record;
            this.VideoSrc = videoSrc;
        }

        public event PropertyChangedEventHandler PropertyChanged = delegate { };

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
