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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : UserControl
    {
        public Menu()
        {
            int counter = 0;

            InitializeComponent();
            if (((MainWindow)Application.Current.MainWindow).kirby == true)
            {
                kirby.Visibility = Visibility.Visible;
                counter++;
            }

            if(((MainWindow)Application.Current.MainWindow).senku == true)
            {
                senku.Visibility = Visibility.Visible;
                counter++;
            }

            if (((MainWindow)Application.Current.MainWindow).nanachi == true)
            {
                nanachi.Visibility = Visibility.Visible;
                counter++;
            }

            if (((MainWindow)Application.Current.MainWindow).dor == true)
            {
                dor.Visibility = Visibility.Visible;
                counter++;
            }

            if (((MainWindow)Application.Current.MainWindow).wilson == true)
            {
                wilson.Visibility = Visibility.Visible;
                counter++;
            }

            if(counter == 5)
            {
                SecretButton.Visibility = Visibility.Visible;
            }

        }

        private void GoToPuzzleSolve(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new EnterLinkViewModel();
        }

        private void GoToHelp(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new HelpViewModel();
        }

        private void GoToCredits(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new CreditsViewModel();
        }

        private void GetSecret(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new ThankYouViewModel();
        }
    }
}
