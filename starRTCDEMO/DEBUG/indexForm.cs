using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;

using System.Windows.Forms;

namespace DEBUG
{
    public partial class indexForm : Form
    {
        //根据DLL中的回调函数的原型声明一个委托类型
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int CPlusAlarmRun(IntPtr data, int dataLen);
        //实例化这个委托。
        static CPlusAlarmRun _alarmCallBack = new CPlusAlarmRun(Receiver.AlarmCallBack);
        [DllImport("TP_VOIP.dll", EntryPoint = "InitBackMsg", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern bool InitBackMsg(CPlusAlarmRun alarmCallBack);

        [DllImport("TP_VOIP.dll", EntryPoint = "YPLogin", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern bool YPLogin(string userID);

        [DllImport("TP_VOIP.dll", EntryPoint = "VoipCallPerson", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern int VoipCallPerson(string userID, ref byte fan);

        [DllImport("TP_VOIP.dll", EntryPoint = "DeleteVoip", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern int DeleteVoip();

        [DllImport("TP_VOIP.dll", EntryPoint = "InitIP", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern bool InitIP(string LocaIP);

        [DllImport("TP_VOIP.dll", EntryPoint = "IPCall", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void IPCall(string AdmIP);

        [DllImport("TP_VOIP.dll", EntryPoint = "stopLive", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void stopLive();

        [DllImport("TP_VOIP.dll", EntryPoint = "BackMsg", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern void BackMsg();

        public indexForm()
        {
            InitializeComponent();
            new ConsoleHelper(textBox3);
        }

        bool isInit = false;

        private void button1_Click(object sender, EventArgs e)
        {
            if (!isInit)
            {
                MessageBox.Show("请启动视频服务");
                return;
            }
            if (String.IsNullOrEmpty(this.textBox1.Text))
            {
                MessageBox.Show("请输入账号");
                return;
            }
            byte[] s = new byte[1024];
            VoipCallPerson(this.textBox1.Text, ref s[0]);
        }
        

        private void button1_Click_2(object sender, EventArgs e)
        {
            string _selfNo = this.selfNo.Text;
            if (string.IsNullOrEmpty(_selfNo))
            {
                MessageBox.Show("请初始化账号");
                return;
            }
            isInit = true;
            bool a = YPLogin(_selfNo);
            bool a1 = InitIP(textBox2.Text);
            if (a)
            {
                this.button1.Enabled = false;
            }
            
        }

        private void indexForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            //DeleteVoip();
        }

        private void indexForm_Shown(object sender, EventArgs e)
        {
            string hostName = Dns.GetHostName();
            IPHostEntry localhost = Dns.GetHostByName(hostName);      
            IPAddress localaddr = localhost.AddressList[0];
            this.textBox2.Text = localaddr.ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
           
            IPCall(textBox1.Text);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (!InitBackMsg(_alarmCallBack))
                MessageBox.Show("ERROR");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            BackMsg();
        }
    }
}
