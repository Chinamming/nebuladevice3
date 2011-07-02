using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Windows.Controls.Ribbon;

namespace WorldEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            // Insert code required on object creation below this point.
        }

        private Editor.EditorInterface editor;
        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var hostWindow = new Editor.Control.HostWindow();
            this.renderArea.Child = hostWindow;
            this.editor = new Editor.EditorInterface();
            this.editor.Open(hostWindow);
            this.propertyEditor.DataContext = this.editor.EditingObject;
        }

        private void RibbonWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            this.editor.Close();
            this.editor = null;
        }
    }
}
