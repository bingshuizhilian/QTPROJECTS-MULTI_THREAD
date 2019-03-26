# QTPROJECTS-MULTI_THREAD

<br>介绍QT的两种多线程的使用方式：</br>
<br>1、通过继承QThread并重写run方法实现多线程，需要注意的是只有run方法运行在新线程中，其余方法均运行于生成此对象的相对的主线程中；</br>
<br>2、继承QObject，通过moveToThread方法实现多线程。</br>
