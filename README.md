#2016暑假课程设计大作业
RDF是由国际WWW组织提出的对万维网上信息进行描述的一个框架。它为Web上的各种应用提供信息描述规范。RDF用
主语、谓语、宾语的三元组形式来描述Web上的资源。
如: tom_Hanks sqouse rita_wilson
在这个大作业中，我们给出任意大小的txt的RDF三元组文件，最大到解压有1.6G的2013某版本DBpedia语义网络知识图谱核心数据集文件。
该类文件（如kb.txt)为纯文本文件，每一行代表一个三元组。我们的目的是要使用RDFind命令检索知识图谱中的数据，具体任务如下（要求
将RDFind布置成为系统命令，即可以在任意目录下可以执行该命令）：
### 任务一：基本检索实现
找到包含所有查询关键字的行并屏幕输出。命令使用如下所示：
cmd>RDFind "hanks 1956" kb.txt
检索包含查询词hanks和1956的三元组并输出。
### 任务二：指定主谓宾检索实现
找到主谓宾处包含所有指定查询关键字的行并屏幕输出。-s代表主语，-p代表谓语，-o代表宾语，命令使用如下所示：
cmd>RDFind -p "spouse" -o "rita wilson" kb.txt
其含义是查找spouse具有关键字“rita wilson"的三元组
### 任务三：命令支持-w功能
cmd>RDFind -w "hanks" kb.txt
-w:hanks这个单词必须被整体匹配，如thanks不能匹配hanks。
### 任务四：连接功能
cmd>RDFind -j1 results1.txt results2.txt
-j1:当results1.txt中的某个三元组与results2.txt中的某个三元组具有相同主语，且两个三元组不完全相同时，在同一行输出两个三元组。
-j2:当results1.txt中的某个三元组与results2.txt中的某个三元组具有相同宾语，且两个三元组不完全相同时，在同一行输出两个三元组。
-j3:当results1.txt中的某个三元组的主语与results2.txt中的某个三元组的宾语相同，且两个三元组不完全相同时，在同一行输出两个三元组。
-j4:当results1.txt中的某个三元组的宾语与results2.txt中的某个三元组的主语相同，且两个三元组不完全相同时，在同一行输出两个三元组。

注意：results1.txt和results2.txt可以是同一个文件！
### 任务五：当任务中其中一个文件非常大时（假设内存放不下，如是1.6G的kb.txt），如何让上述*连接*命令运行得更快。
 
###任务六：实现一个命令GraphSearch
将kb.txt中所有宾语是信息实体（即不被引号包含的主语和宾语）三元组在内存中构建成一个图，从图中某一指定节点出发，在限定步长内查找包含指定关键词的节点，对每个找到的节点，返回从出发节点到找到节点的全路径。
cmd>GraphSearch "tom_hanks" 2 "tom cruise"
表示的是以tom_hanks为出发节点，在图上搜索步长为2以内的（包括2），包含两个关键字Tom和cruise的信息实体






