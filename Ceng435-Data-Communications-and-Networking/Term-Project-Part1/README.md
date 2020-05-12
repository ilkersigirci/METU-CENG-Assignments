Yasin Uysal 2172096
Ali Ilker Sigirci 2171940

## Discovery Part
For the first part, firstly configureR1.sh and configureR2.sh needs to be run on R1 and R2 routers respectively with the following commands:

sh configs/configureR1.sh
sh configs/configureR2.sh

To be able to run them, "chmod +x configs/<script_name>" command must be run first to avoid permission issues. 

Code files are contained in two folders, "discoveryScripts" for the first part and "experimentScripts" for the second part. In "discoveryScripts", there are 5 scripts which are named according to the nodes they need to be run on. 

The order and commands of execution of these scripts must be the following:

python3 d.py
python3 s.py
python3 r2.py
python3 r1.py
python3 r3.py

## Experiment Part
For the second part, firstly node times need to be synchronized so "sudo ntpdate -u pool.ntp.org" command must be run for this purpose. Then, three experiments must be run seperately. For each experiment, following configurations must be done before actual experiment, by filling XX part according to experiment:

sh configs/configureS_XXms.sh
sh configs/configureR3_XXms.sh
sh configs/configureD_XXms.sh

In "experimentScripts", there are 3 scripts which are named according to the nodes they need to be run on.

The order and commands of execution of these scripts must be the following:

python3 d.py
python3 r3.py
python3 s.py


To be able to reconfigure delays on links, following command is used:

sudo tc qdisc del dev [INTERFACE] root netem

To be able to add delays to the links, following command is used:

tc qdisc add dev [INTERFACE] root netem delay <emulation_delay> <error_rate> distribution normal

### Plotting
For plotting Gaussian Distribution run the following command:
python3 gaussianPlot.py

For plotting Enumeration vs End-to-End Delay run the following command:
python3 enum_end-to-end_Plot.py
