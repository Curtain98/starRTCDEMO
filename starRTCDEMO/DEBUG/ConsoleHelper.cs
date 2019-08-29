using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DEBUG
{
    public class ConsoleHelper : TextWriter
    {
        private System.Windows.Forms.TextBox _textBox { set; get; }
        private int maxRowLenght = 0;//textBox中显示的最大行数，若不限制，则置为0
        public ConsoleHelper(System.Windows.Forms.TextBox textBox)
        {
            this._textBox = textBox;
            Console.SetOut(this);
        }
        public override void Write(string value)
        {
            if (_textBox.IsHandleCreated)
                _textBox.BeginInvoke(new ThreadStart(() =>
                {
                    if (maxRowLenght > 0 && _textBox.Lines.Length > maxRowLenght)
                    {
                        int strat = _textBox.GetFirstCharIndexFromLine(0);//获取第0行第一个字符的索引
                        int end = _textBox.GetFirstCharIndexFromLine(10);
                        _textBox.Select(strat, end);//选择文本框中的文本范围
                        _textBox.SelectedText = "";//将当前选定的文本内容置为“”
                        _textBox.AppendText(value + " ");
                    }
                    else
                    {
                        _textBox.AppendText(value + " ");
                    }
                }));
        }

        public override void WriteLine(string value)
        {
            if (_textBox.IsHandleCreated)
                _textBox.BeginInvoke(new ThreadStart(() =>
                {
                    if (maxRowLenght > 0 && _textBox.Lines.Length > maxRowLenght)
                    {
                        int strat = _textBox.GetFirstCharIndexFromLine(0);//获取第0行第一个字符的索引
                        int end = _textBox.GetFirstCharIndexFromLine(10);
                        _textBox.Select(strat, end);//选择文本框中的文本范围
                        _textBox.SelectedText = "";//将当前选定的文本内容置为“”
                        _textBox.AppendText(value + "\r\n");
                    }
                    else
                    {
                        _textBox.AppendText(value + "\r\n");
                    }
                }));
        }

        public override Encoding Encoding//这里要注意,重写wirte必须也要重写编码类型
        {
            get { return Encoding.UTF8; }
        }
    }

}
