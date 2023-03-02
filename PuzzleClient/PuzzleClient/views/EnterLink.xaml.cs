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

using System.Text.RegularExpressions;
using PuzzleClient.viewModels;

using System.IO;
using System.Diagnostics;

namespace PuzzleClient.views
{
    /// <summary>
    /// Interaction logic for EnterLink.xaml
    /// </summary>
    public partial class EnterLink : UserControl
    {
        public EnterLink()
        {
            InitializeComponent();

        }

        public static bool IsValidUrl(string url)
        {
            Regex regex = new Regex("^([A-Z]:[^\\<\\>\\:\"\\|\\?\\*]+)");
            return regex.IsMatch(url);
        }

        private void LinkEntered(object sender, RoutedEventArgs e)
        {
            if (Link.Text != "" && IsValidUrl(Link.Text))
            {
                Application.Current.MainWindow.DataContext = new ImageViewModel();
            }

            else
            {
                Warning.Visibility = Visibility.Visible;
            }
        }
    }

}
