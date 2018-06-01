using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using SQLitePCL;

namespace MyDiary
{

    public class DiaryItemViewModel
    {
        public ObservableCollection<DiaryItem> AllItems = new ObservableCollection<DiaryItem>();

        public static DiaryItemViewModel instance;
        public static DiaryItemViewModel CreatInstance()
        {
            //是否已在内存中存在，不存在就实例化，然后返回此实例
            if (instance == null)
            {
                instance = new DiaryItemViewModel();
            }
            return instance;
        }

        private DiaryItem selectedItem = default(DiaryItem);
        public DiaryItem SelectedItem
        {
            get { return selectedItem; }
            set { this.selectedItem = value; }
        }

        public void AddNewDiary(DateTimeOffset date, string des, string imgSrc, string record, string videoSrc)
        {
            this.AllItems.Add(new DiaryItem(date, des, imgSrc, record, videoSrc));
        }
        public void DelteDiary()
        {
            this.AllItems.Remove(selectedItem);

            this.selectedItem = null;
        }

        public void UpDateDiary(string id, string des, string imgSrc, string record, string videoSrc)
        {
            this.selectedItem.id = id;
            this.selectedItem.description = des;
            this.selectedItem.image_src = imgSrc;
            this.selectedItem.record = record;
            this.selectedItem.videoSrc = videoSrc;
        }

        public void ReadFromDB()
        {
            var db = App.conn;
            using (var statement = db.Prepare(App.SQL_QUERY_VALUE))
            {
                while (SQLiteResult.ROW == statement.Step())
                {
                    DateTimeOffset _date = DateTimeOffset.Parse(statement[0].ToString());
                    this.AllItems.Add(new DiaryItem(_date, statement[1].ToString(), statement[2].ToString(), statement[3].ToString(), statement[4].ToString()));
                }
            }
        }

        /*public DiaryItemViewModel()
        {
            AllItems.Add(new DiaryItem());
            AllItems.Add(new DiaryItem());
        }*/
    }
}
