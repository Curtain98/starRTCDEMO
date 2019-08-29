using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DEBUG
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Msg
    {
        public Int32 Code;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public byte[] note;
    }
    class UtileFunction
    {
        static public string ByteToString(byte[] v_byte)
        {
            if (v_byte == null)
                return "";

            int len1 = v_byte.Length - 10;
            byte[] y = new byte[len1];
            Array.Copy(v_byte, 4, y, 0, len1);
            string v_BarNo = System.Text.Encoding.Default.GetString(y);
            int len = v_BarNo.IndexOf('\0');
            if (len >= 0)
            {
                return v_BarNo.Substring(0, len);
            }
            return v_BarNo;
        }
        
    }
    class Receiver
    {
        public static int AlarmCallBack(IntPtr pData, int dataLen)
        {
            byte[] msgStream = new byte[dataLen];
            Marshal.Copy(pData, msgStream, 0, dataLen);
            Msg msg = new Msg();
            msg = (Msg)InterOperatfFunction.BytesToStruct(msgStream, msg.GetType());
            string _msg = UtileFunction.ByteToString(msg.note);
            Console.WriteLine("Code:{0},Note:{1}", msg.Code,_msg);
            return 0;
        }
    }
}
