using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;

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
        public void AddNewDiary()
        {

        }
        public void DelteDiary()
        {

        }
        /*public DiaryItemViewModel()
        {
            AllItems.Add(new DiaryItem());
            AllItems.Add(new DiaryItem());
        }*/
    }
}
