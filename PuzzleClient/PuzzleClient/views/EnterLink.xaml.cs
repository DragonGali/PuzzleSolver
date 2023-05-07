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
using System.Threading;

using System.IO;
using System.Diagnostics;
using Microsoft.Win32;

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
                File.WriteAllText("C:\\Users\\magshimim\\Desktop\\PuzzleSolver\\puzzle-maker\\ClientLink.txt", Link.Text);
                Process.Start("C:\\Users\\magshimim\\Desktop\\PuzzleSolver\\puzzle-maker\\PuzzleSolver(Server)\\x64\\Release\\PuzzleSolver(Server).exe");
                Application.Current.MainWindow.DataContext = new LoadingViewTemplate();
            }

            else if (Link.Text == "poyo")
            {
                ((MainWindow)Application.Current.MainWindow).kirby = true;
                easterEgg.Text = "Kirby Unlocked";
            }

            else if (Link.Text == "sosoruzekorewa")
            {
                ((MainWindow)Application.Current.MainWindow).senku = true;
                easterEgg.Text = "Senku unlocked";
            }

            else if (Link.Text == "Naaa")
            {
                ((MainWindow)Application.Current.MainWindow).nanachi = true;
                easterEgg.Text = "Nanachi unlocked";
            }

            else if (Link.Text == "Preceed")
            {
                ((MainWindow)Application.Current.MainWindow).dor = true;
                easterEgg.Text = "Dissspointment unlocked";
            }

            else if (Link.Text == "Wilson.P.Higgsburry")
            {
                ((MainWindow)Application.Current.MainWindow).wilson = true;
                easterEgg.Text = "Wilson Unlocked";
            }

            else
            {
                Warning.Visibility = Visibility.Visible;
            }
        }

        private void GoBack(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.DataContext = new MenuViewModel();
        }

        private void FindFile(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                // The user selected a file, so do something with it
                string selectedFilename = openFileDialog.FileName;
                Link.Text = selectedFilename;
            }
        }
    }

}
