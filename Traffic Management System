//Designing a Traffic Signal Control System
//Requirements
//The traffic signal system should control the flow of traffic at an intersection with multiple roads.
//The system should support different types of signals, such as red, yellow, and green.
//The duration of each signal should be configurable and adjustable based on traffic conditions.
//The system should handle the transition between signals smoothly, ensuring safe and efficient traffic flow.
//The system should be able to detect and handle emergency situations, such as an ambulance or fire truck approaching the intersection.
//The system should be scalable and extensible to support additional features and functionality.

using System;
using System.Security.Cryptography.X509Certificates;

namespace TrafficControl
{
    public static class SignalDuration
    {
        public static int RedDuration = 10;
        public static int GreenDuration = 10;
        public static int YellowDuration = 2;

        public static void SetRedDuration(int duration)
        {
            RedDuration = duration;
        }
        public static void SetGreenDuration(int duration)
        {
            GreenDuration = duration;
        }
        public static void SetYellowDuration(int duration)
        {
            YellowDuration = duration;
        }
    }
    public interface Signal
    {
        public void SignalType();
        public Signal GetNextSignal();
        public void SignalWait();
        //public Signal GetSignal(int duration);
    }

    public class Red : Signal
    {
        private static int duration;
        private static Red red = null;
        private Red()
        {

        }
        public static Signal GetSignal(int dur)
        {
            duration = dur;
            if (red == null)
            {
                red = new Red();
            }
            return red;
        }
        //public Red(int duration)
        //{
        //    this.duration = duration;
        //}
        public void SignalType()
        {
            Console.WriteLine("Red");
        }
        public Signal GetNextSignal()
        {
            return Yellow.GetSignal(SignalDuration.YellowDuration);
            //return new Yellow(SignalDuration.YellowDuration);
        }
        public void SignalWait()
        {
            Console.WriteLine($"WAIT for {duration}");
            Thread.Sleep(duration*1000);
            Console.WriteLine("Next is Yellow Signal");
        }
    }

    public class Yellow : Signal
    {
        private static int duration;
        private static Yellow yellow = null;
        private Yellow()
        {

        }
        public static Signal GetSignal(int dur)
        {
            duration = dur;
            if (yellow == null)
            {
                yellow = new Yellow();
            }
            return yellow;
        }
        //public Yellow(int duration)
        //{
        //    this.duration = duration;
        //}
        public void SignalType()
        {
            Console.WriteLine("Yellow");
        }
        public Signal GetNextSignal()
        {
            return Green.GetSignal(SignalDuration.GreenDuration);
            //return new Green(SignalDuration.GreenDuration);
        }
        public void SignalWait()
        {
            Console.WriteLine($"Get Ready, Green signal coming in {duration}");
            Thread.Sleep(duration*1000);
            Console.WriteLine("Next is Green Signal");
        }
    }

    public class Green : Signal
    {
        private static int duration;
        private static Green green = null;
        private Green()
        {

        }
        public static Signal GetSignal(int dur)
        {
            duration = dur;
            if (green == null)
            {
                green = new Green();
            }
            return green;
        }
        //public Green(int duration)
        //{
        //    this.duration = duration;
        //}
        public void SignalType()
        {
            Console.WriteLine("Green");
        }
        public Signal GetNextSignal()
        {
            return Red.GetSignal(SignalDuration.RedDuration);
            //return new Red(SignalDuration.RedDuration);
        }
        public void SignalWait()
        {
            Console.WriteLine($"Run, Run, Green passing by in {duration}");
            Thread.Sleep(duration * 1000);
            Console.WriteLine("Next is Red Signal");
        }
    }

    public class TrafficManager
    {
        private Signal currSignal;
        public TrafficManager(Signal currSignal)
        {
            this.currSignal = currSignal;
        }
        public void Execution(int time)
        {
            for (int i=0;i<time;i++)
            {
                for (int j=0;j<=2;j++)
                {
                    currSignal.SignalType();
                    currSignal.SignalWait();
                    currSignal = currSignal.GetNextSignal();
                }
            }
        }
    }

    public class Program
    {
        public static TrafficManager manager = new TrafficManager(Red.GetSignal(SignalDuration.RedDuration));

        public static void Main()
        {
            Console.WriteLine("Welcome to traffic management system");

            // change the execution, means the no. of times you want to run the system.
            // change the duration of each signal via SignalDuration.Set methods
            manager.Execution(5);

            // In the first implementation, we are creating mulitple objects continuosly. Instead use singleton design pattern. That would be a much beter approach
            // IN future if needed we can make this thread safe as well.
        }    
    }
}
