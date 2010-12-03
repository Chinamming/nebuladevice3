using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using DevComponents.WpfRibbon;
using DevComponents.WpfDock;


namespace ModelEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public partial class MainWindow : DevComponents.WpfRibbon.RibbonWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            // Connect an existing command to the extender so the shared properties can be propagated.
            // See http://www.devcomponents.com/kb/questions.php?questionid=83 for details
            RibbonCommandManager.Connect(ApplicationCommands.Open, new ButtonDropDownCommandExtender("打开", "/images/FolderOpen32.png"));
            RibbonCommandManager.Connect(ApplicationCommands.New, new ButtonDropDownCommandExtender("新建", "/images/Document32.png", "/images/NewDocument.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Close, new ButtonDropDownCommandExtender("退出ModelEditor", "/images/Exit.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Paste, new ButtonDropDownCommandExtender("粘贴", "/images/Paste32.png", "/images/Paste16.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Cut, new ButtonDropDownCommandExtender("剪切", "/images/Cut.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Copy, new ButtonDropDownCommandExtender("复制", "/images/Copy.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Save, new ButtonDropDownCommandExtender("保存", "/images/Save32.png", "/images/Save.png"));
            RibbonCommandManager.Connect(ApplicationCommands.SaveAs, new ButtonDropDownCommandExtender("另存为...", "/images/SaveAs32.png"));
            RibbonCommandManager.Connect(ApplicationCommands.Print, new ButtonDropDownCommandExtender("打印...", "/images/Print32.png"));

            // Create command bindings for some commands
            this.CommandBindings.Add(new CommandBinding(MyCommands.MostRecentlyUsed, MostRecentlyUsedCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.CloseDocument, CloseDocumentCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.Options, CloseDocumentCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Close, CloseCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Open, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.New, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Save, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.SaveAs, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(ApplicationCommands.Print, AppCommandExecute));
            this.CommandBindings.Add(new CommandBinding(MyCommands.BlueTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.BlackTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.SilverTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.OrangeTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.MagentaTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.GreenTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
            this.CommandBindings.Add(new CommandBinding(MyCommands.DarkBlueTheme, ChangeRibbonColor, CanExecuteChangeRibbonColor));
        }

        #region Command Execution
        private eRibbonVisualStyle m_ActiveRibbonColor = eRibbonVisualStyle.Office2007Blue;
        private DevComponents.WpfDock.eDockVisualStyle m_ActiveDockStyle = DevComponents.WpfDock.eDockVisualStyle.Office2007Blue;
        private bool m_CustomColor = false;

        private void MostRecentlyUsedCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            LogAction("Most recently used command executed for '" + e.Parameter.ToString() + "'");
        }

        private void CloseCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void CloseDocumentCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            LogAction("Close active document command executed...");
        }

        private void AppCommandExecute(object sender, ExecutedRoutedEventArgs e)
        {
            if(e.Command is RoutedUICommand)
                LogAction(((RoutedUICommand)e.Command).Text + " command executed...");
            else if(e.Command is RoutedCommand)
                LogAction(((RoutedCommand)e.Command).Name + " command executed...");
        }

        private void CanExecuteChangeRibbonColor(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
            IButtonCommandParameter param = e.Parameter as IButtonCommandParameter;
            if (param == null) return;

            if (e.Command == MyCommands.BlackTheme)
            {
                param.IsChecked = !m_CustomColor && (m_ActiveRibbonColor == eRibbonVisualStyle.Office2007Black);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.SilverTheme)
            {
                param.IsChecked = !m_CustomColor && (m_ActiveRibbonColor == eRibbonVisualStyle.Office2007Silver);
                param.ValueChanged = true;
            }
            else if (e.Command == MyCommands.BlueTheme)
            {
                param.IsChecked = !m_CustomColor && (m_ActiveRibbonColor == eRibbonVisualStyle.Office2007Blue);
                param.ValueChanged = true;
            }
            
        }

        private void ChangeRibbonColor(object sender, ExecutedRoutedEventArgs e)
        {
            ICommand cmd = e.Command;

            //MyCommands.BlackTheme.IsChecked = (cmd == MyCommands.BlackTheme);
            //MyCommands.BlueTheme.IsChecked = (cmd == MyCommands.BlueTheme);
            //MyCommands.SilverTheme.IsChecked = (cmd == MyCommands.SilverTheme);
            //MyCommands.OrangeTheme.IsChecked = (cmd == MyCommands.OrangeTheme);
            //MyCommands.MagentaTheme.IsChecked = (cmd == MyCommands.MagentaTheme);
            //MyCommands.GreenTheme.IsChecked = (cmd == MyCommands.GreenTheme);
            //MyCommands.DarkBlueTheme.IsChecked = (cmd == MyCommands.DarkBlueTheme);
            
            if (cmd == MyCommands.BlueTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Blue, DevComponents.WpfDock.eDockVisualStyle.Office2007Blue, Colors.Transparent);
            }
            else if (cmd == MyCommands.SilverTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Colors.Transparent);
            }
            else if (cmd == MyCommands.BlackTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Black, DevComponents.WpfDock.eDockVisualStyle.Office2007Black, Colors.Transparent);
            }
            // Custom Colors...
            else if (cmd == MyCommands.OrangeTheme)
            {
                // Note that you can use any built-in color table as base table any any color as base color
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Color.FromArgb(255, 255, 128, 0));
            }
            else if (cmd == MyCommands.MagentaTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Color.FromArgb(255, 215, 23, 204));
            }
            else if (cmd == MyCommands.GreenTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Color.FromArgb(255, 0, 149, 4));
            }
            else if (cmd == MyCommands.DarkBlueTheme)
            {
                ChangeColors(eRibbonVisualStyle.Office2007Silver, DevComponents.WpfDock.eDockVisualStyle.Office2007Silver, Colors.SteelBlue);
            }
        }

        private void ChangeColors(eRibbonVisualStyle ribbonColor, DevComponents.WpfDock.eDockVisualStyle dockColor, Color customBaseColor)
        {
            m_ActiveRibbonColor = ribbonColor;
            m_ActiveDockStyle = dockColor;
            m_CustomColor = (customBaseColor != Colors.Transparent);
            if (m_CustomColor)
            {
                AppRibbon.ChangeColorScheme(ribbonColor, customBaseColor);
                AppDock.ChangeColorScheme(dockColor, customBaseColor);
            }
            else
            {
                AppRibbon.ChangeColorScheme(ribbonColor);
                AppDock.ChangeColorScheme(dockColor);
            }
        }
        #endregion

        #region Direct Event Handling
        private void DialogLauncherClicked(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Dialog Launcher Clicked.");
        }
        #endregion

        #region Dock Window Support
        private string m_Layout = "";
        private void SaveDockLayout(object sender, RoutedEventArgs e)
        {
            m_Layout = AppDock.Layout;
            StatusItem1.Content = "Docking Layout Saved.";
        }
        private void LoadDockLayout(object sender, RoutedEventArgs e)
        {
            if (m_Layout.Length > 0)
                AppDock.Layout = m_Layout;
            else
                MessageBox.Show("Click Save to save docking layout, then rearrange the windows and load it by clicking Load.");
        }

        private void DockWindowActivated(object sender, RoutedEventArgs e)
        {
            LogAction(AppDock.ActiveDockWindow.Header.ToString() + " Activated");
        }

        private void DockWindowDeactivated(object sender, RoutedEventArgs e)
        {
            DockWindow dw=e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString()+" Deactivated");
        }

        private void DockWindowClosing(object sender, CancelSourceRoutedEventArgs e)
        {
            // Occurs before DockWindow is closed and you can cancel the closing of the window
            DockWindow dw = e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString() + " Closing");
        }

        private void DockWindowClosed(object sender, RoutedEventArgs e)
        {
            DockWindow dw = e.OriginalSource as DockWindow;
            LogAction(dw.Header.ToString() + " Closed");
        }

        private void LogAction(string text)
        {
            this.textLog.AppendText(DateTime.Now.ToString() + ": " + text + Environment.NewLine);
            this.textLog.ScrollToEnd();
        }
        #endregion

        private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var hostWindow = new Editor.Control.HostWindow();
            this.renderArea.Child = hostWindow;

            // load file tree
            var root = new Editor.IO.DirectoryInfo();
            root.DirectoryURI = "export:";
            root.DirectoryName = "root";
            this.fileTree.ItemsSource = root.SubDirectories;
        }
    }
}
