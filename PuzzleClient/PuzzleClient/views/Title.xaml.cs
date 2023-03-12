using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using PuzzleClient.viewModels;

namespace PuzzleClient.views
{
    /// <summary>
    /// Interaction logic for Title.xaml
    /// </summary>
    public partial class Title : UserControl
    {
        public Title()
        {
            InitializeComponent();
        }

        private void Entered(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new MenuViewModel();
        }
    }
}
