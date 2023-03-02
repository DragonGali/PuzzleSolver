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
using PuzzleClient.views;

namespace PuzzleClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string link;
        public MainWindow()
        {
            InitializeComponent();
            mediaElement.MediaEnded += MediaElement_MediaEnded;
            link = "";
        }
        private void MediaElement_MediaEnded(object sender, RoutedEventArgs e)
        {
            mediaElement.Position = TimeSpan.Zero; // reset position to start
            mediaElement.Play(); // play again
        }

        private void Entered(object sender, RoutedEventArgs e)
        {
            Butt.Visibility = Visibility.Hidden;
            DataContext = new MenuViewModel();
            
        }
    }
}
