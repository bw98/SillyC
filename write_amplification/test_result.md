
> env: Linux 4.14.246-187.474.amzn2.x86_64 (ip-172-31-25-226.us-east-2.compute.internal) 	06/05/2022 	_x86_64_	(1 CPU)
> write 100 1mb files, and read 1kb from these 100 files in 1000 IO based on regular IO and DIO
> collect stat result by command `iostat -x -d 2 60`

For regular write IO [default]

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00    0.00  270.85     0.00 32990.95   243.61     8.56   31.59    0.00   31.59   0.25   6.83


For write DIO

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00    0.00  400.00     0.00 51200.00   256.00     0.87    2.19    0.00    2.19   0.39  15.40


For regular read IO

1st read
Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00   50.51    1.52   808.08    28.28    32.16     0.03    0.66    0.68    0.00   0.66   3.43

2nd+ read
Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.50    0.00   13.93     0.00    58.46     8.39     0.00    0.00    0.00    0.00   0.00   0.00


For regular read IO without system call `sync` [default]

1st read
Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00   50.25    0.50   804.02    36.18    33.11     0.04    0.75    0.72    4.00   0.75   3.82

2nd+ read
Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00    0.00    0.50     0.00    36.00   144.00     0.00    0.00    0.00    0.00   0.00   0.00


For read DIO

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     4.55  505.05   24.75   505.05   122.98     2.37     0.29    0.55    0.54    0.82   0.55  29.09


For read DIO without system call `sync`

Device:         rrqm/s   wrqm/s     r/s     w/s    rkB/s    wkB/s avgrq-sz avgqu-sz   await r_await w_await  svctm  %util
xvda              0.00     0.00  505.05    0.51   505.05    36.36     2.14     0.28    0.55    0.55    4.00   0.55  27.88

