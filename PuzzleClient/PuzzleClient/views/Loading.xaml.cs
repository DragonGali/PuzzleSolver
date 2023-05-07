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
using System.Threading;

namespace PuzzleClient.views
{
    /// <summary>
    /// Interaction logic for Loading.xaml
    /// </summary>
    public partial class Loading : UserControl
    {
        string[] hints = { "A sound a hungry pink ball makes", "catchprase from a very scientific Anime", "How many A's does this even need?", "A misspelled word" , "Character from an indie survival game"};


        public Loading()
        {
            InitializeComponent();
            Random random = new Random();
            int randomIndex = random.Next(hints.Length);
            HintsBar.Text = hints[randomIndex];
        }

        private void GoForward(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new ImageViewModel();
        }


    }
}
