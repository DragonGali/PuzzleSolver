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
using System.Media;

using PuzzleClient.viewModels;
using PuzzleClient.views;

namespace PuzzleClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // shhh its a secret
        public bool kirby = false;
        public bool senku = false;
        public bool nanachi = false;
        public bool dor = false;
        public bool wilson = false;

        public SoundPlayer player;
        public MainWindow()
        {
            InitializeComponent();
            // music that I (definately didnt steal)
            player = new SoundPlayer("C:\\Users\\magshimim\\Desktop\\PuzzleSolver\\puzzle-maker\\PuzzleClient\\PuzzleClient\\Resources\\lofi_girl_dreams_113883.wav");
            player.PlayLooping();

            DataContext = new Title();
        }
    }
}
