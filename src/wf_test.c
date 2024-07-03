#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "utils.h"
#include "wf_test.h"

T3DMat4FP* wfMatFP;
T3DModel *modelWF;
rspq_block_t *dplWF;

T3DVec3 wfVerts[802] =
{
       {{-204, 655, -558}},
       {{166, 917, -188}},
       {{166, 655, -188}},
       {{-204, 917, -558}},
       {{428, 655, -319}},
       {{297, 655, -319}},
       {{297, 917, -319}},
       {{-358, 655, -188}},
       {{-358, 917, -188}},
       {{297, 655, 205}},
       {{297, 655, -188}},
       {{297, 917, 205}},
       {{166, 917, 336}},
       {{-358, 655, 336}},
       {{-358, 917, 336}},
       {{35, 655, 336}},
       {{166, 655, 336}},
       {{35, 518, 336}},
       {{-358, 518, 336}},
       {{190, 917, -732}},
       {{92, 884, -634}},
       {{92, 917, -634}},
       {{953, 131, 992}},
       {{730, 131, 992}},
       {{730, 65, 992}},
       {{953, 65, 992}},
       {{125, 917, -601}},
       {{125, 884, -601}},
       {{223, 884, -700}},
       {{223, 917, -700}},
       {{256, 917, -667}},
       {{256, 884, -667}},
       {{256, 884, -765}},
       {{190, 884, -732}},
       {{157, 917, -765}},
       {{157, 884, -765}},
       {{256, 917, -765}},
       {{1084, 0, -188}},
       {{1215, 65, -57}},
       {{1215, 0, -57}},
       {{1051, 65, 992}},
       {{953, 0, -188}},
       {{953, 65, -188}},
       {{1084, 65, -188}},
       {{1215, 65, 992}},
       {{1215, 0, 992}},
       {{382, 917, -714}},
       {{431, 917, -761}},
       {{494, 852, -646}},
       {{426, 917, -535}},
       {{491, 917, -516}},
       {{379, 917, -583}},
       {{363, 917, -649}},
       {{625, 917, -644}},
       {{606, 917, -579}},
       {{497, 917, -777}},
       {{562, 917, -759}},
       {{609, 917, -710}},
       {{557, 917, -532}},
       {{611, 852, -583}},
       {{660, 852, -630}},
       {{723, 786, -515}},
       {{656, 852, -404}},
       {{721, 852, -385}},
       {{609, 852, -452}},
       {{593, 852, -518}},
       {{854, 852, -513}},
       {{835, 852, -448}},
       {{726, 852, -646}},
       {{791, 852, -627}},
       {{838, 852, -579}},
       {{786, 852, -401}},
       {{480, 917, -354}},
       {{529, 917, -401}},
       {{592, 852, -286}},
       {{525, 917, -174}},
       {{590, 917, -155}},
       {{478, 917, -223}},
       {{462, 917, -289}},
       {{723, 917, -283}},
       {{704, 917, -218}},
       {{595, 917, -417}},
       {{660, 917, -398}},
       {{707, 917, -349}},
       {{655, 917, -171}},
       {{560, 0, 1385}},
       {{429, 65, 1254}},
       {{429, 0, 1254}},
       {{1215, 65, 1254}},
       {{1215, 0, 1254}},
       {{1084, 65, 1385}},
       {{1084, 0, 1385}},
       {{429, 65, 992}},
       {{429, 0, 992}},
       {{560, 65, 1385}},
       {{580, 1048, 28}},
       {{580, 1048, -43}},
       {{642, 1048, -78}},
       {{642, 1048, 63}},
       {{703, 1048, 28}},
       {{703, 1048, -43}},
       {{33, 623, 504}},
       {{30, 655, 479}},
       {{37, 655, 530}},
       {{-153, 655, 585}},
       {{-161, 623, 533}},
       {{-113, 655, 552}},
       {{-202, 655, 565}},
       {{-210, 655, 514}},
       {{-169, 655, 481}},
       {{-120, 655, 501}},
       {{94, 655, 520}},
       {{94, 662, 520}},
       {{356, 662, 520}},
       {{94, 655, 546}},
       {{94, 662, 546}},
       {{356, 655, 546}},
       {{356, 662, 546}},
       {{356, 655, 520}},
       {{-110, 917, -434}},
       {{-124, 1219, -420}},
       {{-110, 1219, -434}},
       {{-75, 1219, -400}},
       {{-75, 917, -400}},
       {{-89, 1219, -386}},
       {{-89, 917, -386}},
       {{-124, 917, -420}},
       {{730, 236, 874}},
       {{730, 590, -57}},
       {{691, 236, 467}},
       {{730, 262, 874}},
       {{730, 262, 926}},
       {{677, 236, 979}},
       {{677, 262, 979}},
       {{677, 236, 874}},
       {{822, 131, 926}},
       {{822, 262, 874}},
       {{822, 262, 926}},
       {{822, 275, 336}},
       {{822, 590, -57}},
       {{822, 275, -843}},
       {{822, 0, -188}},
       {{822, 0, -843}},
       {{822, 275, -188}},
       {{730, 131, 926}},
       {{822, 590, -188}},
       {{730, 262, 992}},
       {{-358, 236, 979}},
       {{-738, 262, 992}},
       {{-738, 0, 992}},
       {{730, 0, 992}},
       {{-358, 262, 979}},
       {{-358, 236, 730}},
       {{-358, 262, 730}},
       {{-738, 0, 730}},
       {{-738, 262, 730}},
       {{-934, 98, -450}},
       {{-934, 0, 107}},
       {{-934, 98, 107}},
       {{-738, 98, 107}},
       {{-738, 0, 107}},
       {{-620, 98, -450}},
       {{-934, 0, -450}},
       {{-620, 0, -450}},
       {{730, 590, -188}},
       {{822, 272, -849}},
       {{730, 272, -849}},
       {{822, 590, -285}},
       {{730, 543, -285}},
       {{730, 590, -285}},
       {{822, 543, -285}},
       {{822, 496, -479}},
       {{822, 450, -479}},
       {{730, 450, -479}},
       {{822, 543, -382}},
       {{730, 496, -382}},
       {{730, 543, -382}},
       {{822, 496, -382}},
       {{730, 496, -479}},
       {{822, 450, -577}},
       {{730, 403, -577}},
       {{730, 450, -577}},
       {{822, 403, -577}},
       {{822, 406, -674}},
       {{822, 356, -674}},
       {{730, 356, -674}},
       {{730, 406, -674}},
       {{822, 357, -723}},
       {{919, 340, -76}},
       {{919, 340, -37}},
       {{951, 327, -32}},
       {{951, 327, -81}},
       {{820, 327, -89}},
       {{951, 275, -89}},
       {{820, 275, -89}},
       {{935, 327, -89}},
       {{820, 340, -76}},
       {{935, 327, -24}},
       {{820, 340, -37}},
       {{820, 327, -24}},
       {{820, 275, -24}},
       {{951, 275, -24}},
       {{741, 340, 290}},
       {{840, 340, 251}},
       {{741, 340, 251}},
       {{840, 340, 290}},
       {{872, 327, 295}},
       {{872, 327, 247}},
       {{741, 327, 238}},
       {{872, 275, 238}},
       {{741, 275, 238}},
       {{855, 327, 238}},
       {{855, 327, 304}},
       {{741, 327, 304}},
       {{741, 275, 304}},
       {{872, 275, 304}},
       {{792, 275, 172}},
       {{923, 275, 172}},
       {{906, 327, 172}},
       {{923, 275, 41}},
       {{906, 327, 41}},
       {{923, 327, 58}},
       {{891, 340, 68}},
       {{923, 327, 156}},
       {{891, 340, 146}},
       {{792, 340, 68}},
       {{792, 327, 172}},
       {{792, 340, 146}},
       {{792, 327, 41}},
       {{792, 275, 41}},
       {{730, 275, -843}},
       {{730, 590, -319}},
       {{730, 405, -674}},
       {{-358, 655, 600}},
       {{-401, 655, 600}},
       {{-358, 458, 730}},
       {{-620, 622, -319}},
       {{-620, 458, 25}},
       {{-620, 622, 74}},
       {{-620, 458, -270}},
       {{-489, 655, 336}},
       {{-620, 655, 74}},
       {{546, 590, -57}},
       {{428, 648, -57}},
       {{428, 655, -57}},
       {{559, 590, -57}},
       {{546, 590, -188}},
       {{559, 590, -188}},
       {{428, 648, -188}},
       {{428, 655, -188}},
       {{-620, 655, -674}},
       {{953, 0, -843}},
       {{953, 275, -843}},
       {{-620, 0, -1105}},
       {{-620, 426, -270}},
       {{-620, 655, -319}},
       {{533, 275, -1105}},
       {{35, 0, -1105}},
       {{533, 308, -1105}},
       {{953, 0, -1105}},
       {{-620, 262, 730}},
       {{-620, 426, 25}},
       {{166, 655, 369}},
       {{330, 236, 205}},
       {{330, 655, 205}},
       {{166, 236, 369}},
       {{-620, 98, 107}},
       {{953, 275, -1105}},
       {{428, 655, 205}},
       {{559, 236, 467}},
       {{35, 458, 730}},
       {{82, 655, 600}},
       {{35, 655, 600}},
       {{35, 236, 730}},
       {{533, 275, -843}},
       {{-718, 426, -105}},
       {{-751, 426, -105}},
       {{-718, 458, -105}},
       {{-620, 308, -257}},
       {{-797, 341, -269}},
       {{-620, 341, -269}},
       {{-785, 308, -257}},
       {{-797, 341, -53}},
       {{-620, 308, -66}},
       {{-620, 341, -53}},
       {{-785, 308, -66}},
       {{-718, 426, -138}},
       {{-751, 458, -105}},
       {{-751, 426, -138}},
       {{-751, 458, -138}},
       {{-718, 458, -138}},
       {{-718, 458, -245}},
       {{-718, 622, -270}},
       {{-718, 458, -270}},
       {{-849, 426, -270}},
       {{-849, 426, 25}},
       {{-685, 458, -245}},
       {{-685, 622, -245}},
       {{-718, 622, -245}},
       {{-784, 458, -245}},
       {{-816, 622, -245}},
       {{-816, 458, -245}},
       {{-685, 622, -270}},
       {{-685, 458, -270}},
       {{-784, 622, -245}},
       {{-784, 458, 25}},
       {{-784, 622, 25}},
       {{-816, 622, 25}},
       {{-816, 622, -270}},
       {{-816, 458, -270}},
       {{-784, 622, -270}},
       {{-784, 458, -270}},
       {{-784, 458, 1}},
       {{-784, 622, 1}},
       {{-816, 458, 25}},
       {{-816, 622, 1}},
       {{-816, 458, 1}},
       {{-685, 458, 1}},
       {{-685, 622, 1}},
       {{-685, 622, 25}},
       {{-685, 458, 25}},
       {{-718, 622, 25}},
       {{-718, 458, 25}},
       {{-718, 622, 1}},
       {{-718, 458, 1}},
       {{-882, 622, -318}},
       {{-882, 655, -318}},
       {{-620, 655, -318}},
       {{-882, 655, 74}},
       {{-882, 622, 74}},
       {{-849, 458, 25}},
       {{-620, 622, -318}},
       {{-849, 458, -270}},
       {{-358, 459, 730}},
       {{-358, 655, 730}},
       {{289, 917, -798}},
       {{406, 885, -805}},
       {{419, 917, -798}},
       {{406, 885, -922}},
       {{419, 917, -929}},
       {{302, 885, -922}},
       {{289, 917, -929}},
       {{302, 885, -805}},
       {{953, 275, -319}},
       {{953, 0, -450}},
       {{953, 275, -450}},
       {{953, 0, -319}},
       {{822, 275, -319}},
       {{822, 0, -319}},
       {{822, 0, -450}},
       {{822, 275, -450}},
       {{953, 275, -581}},
       {{953, 0, -712}},
       {{953, 275, -712}},
       {{953, 0, -581}},
       {{822, 275, -581}},
       {{822, 0, -581}},
       {{822, 0, -712}},
       {{822, 275, -712}},
       {{876, 275, -450}},
       {{876, 262, -450}},
       {{876, 262, -581}},
       {{876, 275, -581}},
       {{886, 275, -188}},
       {{886, 262, -188}},
       {{886, 262, -318}},
       {{886, 275, -318}},
       {{953, 262, -712}},
       {{953, 262, -843}},
       {{468, 623, 697}},
       {{297, 623, 500}},
       {{468, 623, 500}},
       {{468, 655, 697}},
       {{468, 655, 500}},
       {{297, 655, 697}},
       {{297, 623, 697}},
       {{297, 655, 500}},
       {{35, 459, 730}},
       {{35, 655, 730}},
       {{-151, 917, 74}},
       {{-227, 1310, -2}},
       {{-227, 917, -2}},
       {{-227, 917, -112}},
       {{-227, 1310, -112}},
       {{-151, 1310, -188}},
       {{-151, 917, -188}},
       {{-227, 970, -29}},
       {{-227, 917, -29}},
       {{-151, 1310, 74}},
       {{-41, 917, -188}},
       {{-41, 1310, -188}},
       {{35, 1310, -112}},
       {{-41, 917, 74}},
       {{-41, 1310, 74}},
       {{35, 917, -2}},
       {{35, 1310, -2}},
       {{35, 917, -112}},
       {{-174, 917, -29}},
       {{-227, 970, -84}},
       {{-227, 917, -84}},
       {{-174, 917, -84}},
       {{-174, 970, -29}},
       {{-174, 970, -84}},
       {{-225, 1174, -5}},
       {{-225, 1147, -5}},
       {{-299, 1147, 69}},
       {{-299, 1174, 69}},
       {{-222, 1147, 147}},
       {{-222, 1174, 147}},
       {{-147, 1147, 73}},
       {{-147, 1174, 73}},
       {{-224, 1148, -112}},
       {{-224, 1122, -112}},
       {{-329, 1122, -112}},
       {{-329, 1148, -112}},
       {{-329, 1122, -2}},
       {{-329, 1148, -2}},
       {{-224, 1122, -2}},
       {{-224, 1148, -2}},
       {{-121, 1122, -159}},
       {{-121, 1096, -159}},
       {{-195, 1096, -233}},
       {{-195, 1122, -233}},
       {{-272, 1096, -155}},
       {{-272, 1122, -155}},
       {{-198, 1096, -81}},
       {{-198, 1122, -81}},
       {{-41, 1097, -185}},
       {{-41, 1071, -185}},
       {{-41, 1071, -290}},
       {{-41, 1097, -290}},
       {{-151, 1071, -290}},
       {{-151, 1097, -290}},
       {{-151, 1071, -185}},
       {{-151, 1097, -185}},
       {{6, 1071, -81}},
       {{6, 1045, -81}},
       {{80, 1045, -156}},
       {{80, 1071, -156}},
       {{3, 1045, -233}},
       {{3, 1071, -233}},
       {{-71, 1045, -159}},
       {{-71, 1071, -159}},
       {{32, 1046, -2}},
       {{32, 1019, -2}},
       {{137, 1019, -2}},
       {{137, 1046, -2}},
       {{137, 1019, -112}},
       {{137, 1046, -112}},
       {{32, 1019, -112}},
       {{32, 1046, -112}},
       {{-71, 1020, 45}},
       {{-71, 994, 45}},
       {{3, 994, 119}},
       {{3, 1020, 119}},
       {{80, 994, 42}},
       {{80, 1020, 42}},
       {{6, 994, -32}},
       {{6, 1020, -32}},
       {{-151, 994, 71}},
       {{-151, 968, 71}},
       {{-151, 968, 176}},
       {{-151, 994, 176}},
       {{-41, 968, 176}},
       {{-41, 994, 176}},
       {{-41, 968, 71}},
       {{-41, 994, 71}},
       {{-151, 1376, -188}},
       {{-41, 1376, 74}},
       {{35, 1376, -2}},
       {{35, 1376, -112}},
       {{-41, 1376, -188}},
       {{-151, 1376, 74}},
       {{-227, 1376, -112}},
       {{-227, 1376, -2}},
       {{16, 1376, -104}},
       {{16, 1363, -10}},
       {{16, 1376, -10}},
       {{16, 1363, -104}},
       {{-208, 1376, -10}},
       {{-208, 1363, -104}},
       {{-208, 1376, -104}},
       {{-49, 1376, -169}},
       {{-49, 1363, -169}},
       {{-143, 1376, -169}},
       {{-143, 1363, -169}},
       {{-49, 1363, 55}},
       {{-49, 1376, 55}},
       {{-208, 1363, -10}},
       {{-143, 1376, 55}},
       {{-143, 1363, 55}},
       {{-128, 655, 336}},
       {{-194, 655, 480}},
       {{-194, 655, 336}},
       {{-128, 655, 480}},
       {{-161, 721, 480}},
       {{-541, 262, 966}},
       {{-594, 131, 966}},
       {{-594, 262, 966}},
       {{-541, 131, 966}},
       {{-541, 262, 913}},
       {{-541, 131, 913}},
       {{-594, 262, 913}},
       {{-594, 131, 913}},
       {{330, 623, 500}},
       {{418, 623, 468}},
       {{418, 623, 500}},
       {{418, 655, 468}},
       {{418, 655, 500}},
       {{330, 623, 468}},
       {{330, 655, 468}},
       {{330, 655, 500}},
       {{330, 623, 467}},
       {{418, 623, 435}},
       {{418, 623, 467}},
       {{418, 655, 435}},
       {{418, 655, 467}},
       {{330, 623, 435}},
       {{330, 655, 435}},
       {{330, 655, 467}},
       {{418, 623, 402}},
       {{418, 655, 402}},
       {{330, 623, 402}},
       {{330, 655, 402}},
       {{418, 623, 369}},
       {{418, 655, 369}},
       {{330, 623, 369}},
       {{330, 655, 369}},
       {{418, 623, 337}},
       {{418, 655, 337}},
       {{330, 623, 337}},
       {{330, 655, 337}},
       {{330, 623, 336}},
       {{418, 623, 304}},
       {{418, 623, 336}},
       {{418, 655, 304}},
       {{418, 655, 336}},
       {{330, 623, 304}},
       {{330, 655, 304}},
       {{330, 655, 336}},
       {{418, 623, 271}},
       {{418, 655, 271}},
       {{330, 623, 271}},
       {{330, 655, 271}},
       {{418, 623, 238}},
       {{418, 655, 238}},
       {{330, 623, 238}},
       {{330, 655, 238}},
       {{418, 623, 206}},
       {{418, 655, 206}},
       {{330, 623, 206}},
       {{330, 655, 206}},
       {{429, 655, -57}},
       {{429, 648, -57}},
       {{429, 655, -187}},
       {{429, 648, -187}},
       {{468, 629, -57}},
       {{468, 635, -187}},
       {{468, 635, -57}},
       {{442, 648, -57}},
       {{442, 642, -57}},
       {{442, 648, -187}},
       {{442, 642, -187}},
       {{455, 635, -187}},
       {{455, 642, -187}},
       {{455, 635, -57}},
       {{455, 642, -57}},
       {{468, 629, -187}},
       {{494, 616, -187}},
       {{494, 622, -187}},
       {{494, 616, -57}},
       {{481, 622, -187}},
       {{481, 629, -187}},
       {{481, 622, -57}},
       {{481, 629, -57}},
       {{494, 622, -57}},
       {{507, 610, -187}},
       {{507, 616, -187}},
       {{507, 610, -57}},
       {{507, 616, -57}},
       {{520, 603, -187}},
       {{520, 610, -187}},
       {{520, 603, -57}},
       {{520, 610, -57}},
       {{533, 596, -187}},
       {{533, 603, -187}},
       {{533, 596, -57}},
       {{533, 603, -57}},
       {{546, 590, -187}},
       {{546, 596, -187}},
       {{546, 596, -57}},
       {{1215, 98, 664}},
       {{1215, 98, -57}},
       {{1215, 98, 1254}},
       {{1084, 98, 1385}},
       {{953, 98, -188}},
       {{1084, 98, -188}},
       {{428, 65, 1254}},
       {{428, 98, 1254}},
       {{559, 98, 1385}},
       {{1215, 65, 664}},
       {{559, 65, 1385}},
       {{428, 65, 992}},
       {{428, 98, 992}},
       {{677, 236, 926}},
       {{-731, 498, -122}},
       {{-731, 341, -122}},
       {{-733, 341, -125}},
       {{-736, 498, -125}},
       {{-736, 341, -125}},
       {{-738, 341, -122}},
       {{-738, 498, -122}},
       {{-733, 498, -125}},
       {{-733, 498, -119}},
       {{-736, 498, -119}},
       {{-733, 341, -119}},
       {{-736, 341, -119}},
       {{-163, 1428, -18}},
       {{-136, 1428, -124}},
       {{-57, 1428, -124}},
       {{-29, 1428, -97}},
       {{-29, 1428, -18}},
       {{-52, 1428, 9}},
       {{-136, 1428, 9}},
       {{-163, 1428, -97}},
       {{-747, 655, -122}},
       {{-749, 1193, -119}},
       {{-749, 655, -119}},
       {{-753, 1193, -125}},
       {{-755, 1193, -122}},
       {{-753, 1193, -119}},
       {{-747, 1193, -122}},
       {{-749, 1193, -125}},
       {{-753, 655, -119}},
       {{-755, 655, -122}},
       {{-749, 655, -125}},
       {{-753, 655, -125}},
       {{-738, 295, 992}},
       {{-358, 295, 992}},
       {{-358, 262, 992}},
       {{-620, 681, 74}},
       {{-489, 681, 336}},
       {{-166, 655, -782}},
       {{297, 681, -319}},
       {{-166, 681, -782}},
       {{642, 1114, 63}},
       {{730, 622, -57}},
       {{559, 622, -57}},
       {{428, 688, -57}},
       {{428, 688, 205}},
       {{580, 1114, 28}},
       {{-620, 681, -674}},
       {{580, 1114, -43}},
       {{642, 1114, -78}},
       {{703, 1114, -43}},
       {{703, 1114, 28}},
       {{-620, 681, -319}},
       {{-935, 98, -450}},
       {{-620, 131, -450}},
       {{-935, 131, -450}},
       {{953, 308, -1105}},
       {{953, 308, -843}},
       {{-935, 98, 107}},
       {{-935, 131, 107}},
       {{-738, 131, 107}},
       {{-738, 295, 730}},
       {{953, 275, -188}},
       {{953, 275, 336}},
       {{953, 131, 926}},
       {{953, 65, 730}},
       {{-128, 1363, -89}},
       {{-128, 1428, -89}},
       {{-63, 1428, -89}},
       {{-128, 1363, -24}},
       {{-128, 1428, -24}},
       {{-63, 1363, -89}},
       {{-63, 1428, -24}},
       {{-63, 1363, -24}},
       {{1018, 65, 271}},
       {{1018, 78, 206}},
       {{1018, 65, 206}},
       {{1018, 65, 9}},
       {{1018, 78, 9}},
       {{1018, 78, -57}},
       {{1018, 65, -57}},
       {{1117, 65, -89}},
       {{1117, 78, -89}},
       {{1149, 78, -57}},
       {{1149, 65, -57}},
       {{1051, 65, -89}},
       {{1051, 78, -89}},
       {{1117, 65, 173}},
       {{1149, 78, 206}},
       {{1149, 65, 206}},
       {{1018, 78, 271}},
       {{1051, 78, 173}},
       {{1051, 65, 173}},
       {{1117, 78, 173}},
       {{1051, 65, 304}},
       {{1149, 78, 271}},
       {{1149, 65, 271}},
       {{1117, 78, 304}},
       {{1117, 65, 304}},
       {{1051, 78, 304}},
       {{1149, 65, 9}},
       {{1149, 78, 9}},
       {{1117, 78, 42}},
       {{1051, 65, 42}},
       {{1051, 78, 42}},
       {{1117, 65, 42}},
       {{644, 65, 1310}},
       {{644, 73, 1310}},
       {{644, 73, 1263}},
       {{1149, 65, 1188}},
       {{1149, 79, 1254}},
       {{1149, 65, 1254}},
       {{1149, 79, 1188}},
       {{1117, 65, 1156}},
       {{1117, 79, 1156}},
       {{1117, 79, 1287}},
       {{1117, 65, 1287}},
       {{714, 65, 1240}},
       {{738, 73, 1263}},
       {{738, 65, 1263}},
       {{644, 65, 1263}},
       {{667, 73, 1240}},
       {{667, 65, 1240}},
       {{714, 73, 1240}},
       {{667, 65, 1334}},
       {{667, 73, 1334}},
       {{738, 73, 1310}},
       {{738, 65, 1310}},
       {{714, 73, 1334}},
       {{714, 65, 1334}},
       {{1018, 65, 1254}},
       {{1018, 79, 1188}},
       {{1018, 65, 1188}},
       {{1051, 65, 1156}},
       {{1051, 79, 1156}},
       {{1018, 79, 1254}},
       {{1051, 65, 1287}},
       {{1051, 79, 1287}},
       {{196, 727, -326}},
       {{92, 727, -300}},
       {{157, 727, -364}},
       {{92, 746, -300}},
       {{157, 746, -364}},
       {{131, 746, -261}},
       {{131, 727, -261}},
       {{196, 746, -326}},
       {{246, 894, -275}},
       {{143, 894, -249}},
       {{207, 894, -314}},
       {{182, 894, -210}},
       {{182, 914, -210}},
       {{246, 914, -275}},
       {{207, 914, -314}},
       {{143, 914, -249}},
       {{109, 917, -245}},
       {{130, 714, -243}},
       {{109, 714, -245}},
       {{130, 917, -243}},
       {{132, 917, -222}},
       {{132, 714, -222}},
       {{199, 917, 140}},
       {{265, 983, 140}},
       {{265, 917, 140}},
       {{199, 983, 140}},
       {{199, 917, 218}},
       {{199, 983, 218}},
       {{265, 983, 218}},
       {{265, 917, 218}},
       {{1051, 65, 926}},
       {{730, 357, -723}},
       {{-96, 1560, -57}},
       {{-161, 721, 336}},
       {{822, 275, 337}},
       {{855, 244, 464}},
       {{887, 249, 432}},
       {{855, 154, 846}},
       {{822, 205, 623}},
       {{887, 192, 655}},
       {{855, 205, 655}},
       {{920, 153, 814}},
       {{953, 275, 337}},
       {{920, 210, 559}},
       {{887, 228, 528}},
       {{745, 275, -581}},
       {{745, 275, -450}},
       {{755, 275, -318}},
       {{755, 275, -188}},
       {{559, 590, -187}},
       {{887, 275, -430}},
       {{841, 275, -338}},
       {{933, 275, -338}},
       {{887, 275, -692}},
       {{841, 275, -601}},
       {{933, 275, -601}},
       {{-358, 249, 205}},
       {{-358, 249, 992}},
       {{730, 249, 992}},
       {{730, 249, 205}}
};

int wfWallCount = 862;
Surface wfWall[862];
int wfSlopeCount = 62;
Surface wfSlope[62];
int wfFloorCount = 264;
Surface wfFloor[264];

void wf_init(void){

    wfWall[0].posA = wfVerts[0]; wfWall[0].posB = wfVerts[1]; wfWall[0].posC = wfVerts[2];
    wfWall[1].posA = wfVerts[0]; wfWall[1].posB = wfVerts[3]; wfWall[1].posC = wfVerts[1];
    wfWall[2].posA = wfVerts[4]; wfWall[2].posB = wfVerts[5]; wfWall[2].posC = wfVerts[6];
    wfWall[3].posA = wfVerts[7]; wfWall[3].posB = wfVerts[8]; wfWall[3].posC = wfVerts[3];
    wfWall[4].posA = wfVerts[7]; wfWall[4].posB = wfVerts[3]; wfWall[4].posC = wfVerts[0];
    wfWall[5].posA = wfVerts[9]; wfWall[5].posB = wfVerts[10]; wfWall[5].posC = wfVerts[11];
    wfWall[6].posA = wfVerts[9]; wfWall[6].posB = wfVerts[11]; wfWall[6].posC = wfVerts[12];
    wfWall[7].posA = wfVerts[10]; wfWall[7].posB = wfVerts[6]; wfWall[7].posC = wfVerts[11];
    wfWall[8].posA = wfVerts[7]; wfWall[8].posB = wfVerts[13]; wfWall[8].posC = wfVerts[8];
    wfWall[9].posA = wfVerts[13]; wfWall[9].posB = wfVerts[14]; wfWall[9].posC = wfVerts[8];
    wfWall[10].posA = wfVerts[13]; wfWall[10].posB = wfVerts[15]; wfWall[10].posC = wfVerts[14];
    wfWall[11].posA = wfVerts[15]; wfWall[11].posB = wfVerts[16]; wfWall[11].posC = wfVerts[12];
    wfWall[12].posA = wfVerts[12]; wfWall[12].posB = wfVerts[14]; wfWall[12].posC = wfVerts[15];
    wfWall[13].posA = wfVerts[9]; wfWall[13].posB = wfVerts[12]; wfWall[13].posC = wfVerts[16];
    wfWall[14].posA = wfVerts[4]; wfWall[14].posB = wfVerts[6]; wfWall[14].posC = wfVerts[10];
    wfWall[15].posA = wfVerts[17]; wfWall[15].posB = wfVerts[15]; wfWall[15].posC = wfVerts[18];
    wfWall[16].posA = wfVerts[13]; wfWall[16].posB = wfVerts[18]; wfWall[16].posC = wfVerts[15];
    wfWall[17].posA = wfVerts[2]; wfWall[17].posB = wfVerts[1]; wfWall[17].posC = wfVerts[6];
    wfWall[18].posA = wfVerts[5]; wfWall[18].posB = wfVerts[2]; wfWall[18].posC = wfVerts[6];
    wfWall[19].posA = wfVerts[19]; wfWall[19].posB = wfVerts[20]; wfWall[19].posC = wfVerts[21];
    wfWall[20].posA = wfVerts[22]; wfWall[20].posB = wfVerts[23]; wfWall[20].posC = wfVerts[24];
    wfWall[21].posA = wfVerts[22]; wfWall[21].posB = wfVerts[24]; wfWall[21].posC = wfVerts[25];
    wfWall[22].posA = wfVerts[26]; wfWall[22].posB = wfVerts[27]; wfWall[22].posC = wfVerts[28];
    wfWall[23].posA = wfVerts[26]; wfWall[23].posB = wfVerts[28]; wfWall[23].posC = wfVerts[29];
    wfWall[24].posA = wfVerts[21]; wfWall[24].posB = wfVerts[20]; wfWall[24].posC = wfVerts[27];
    wfWall[25].posA = wfVerts[21]; wfWall[25].posB = wfVerts[27]; wfWall[25].posC = wfVerts[26];
    wfWall[26].posA = wfVerts[30]; wfWall[26].posB = wfVerts[31]; wfWall[26].posC = wfVerts[32];
    wfWall[27].posA = wfVerts[19]; wfWall[27].posB = wfVerts[33]; wfWall[27].posC = wfVerts[20];
    wfWall[28].posA = wfVerts[34]; wfWall[28].posB = wfVerts[35]; wfWall[28].posC = wfVerts[33];
    wfWall[29].posA = wfVerts[34]; wfWall[29].posB = wfVerts[33]; wfWall[29].posC = wfVerts[19];
    wfWall[30].posA = wfVerts[36]; wfWall[30].posB = wfVerts[32]; wfWall[30].posC = wfVerts[35];
    wfWall[31].posA = wfVerts[36]; wfWall[31].posB = wfVerts[35]; wfWall[31].posC = wfVerts[34];
    wfWall[32].posA = wfVerts[30]; wfWall[32].posB = wfVerts[32]; wfWall[32].posC = wfVerts[36];
    wfWall[33].posA = wfVerts[29]; wfWall[33].posB = wfVerts[31]; wfWall[33].posC = wfVerts[30];
    wfWall[34].posA = wfVerts[29]; wfWall[34].posB = wfVerts[28]; wfWall[34].posC = wfVerts[31];
    wfWall[35].posA = wfVerts[37]; wfWall[35].posB = wfVerts[38]; wfWall[35].posC = wfVerts[39];
    wfWall[36].posA = wfVerts[25]; wfWall[36].posB = wfVerts[40]; wfWall[36].posC = wfVerts[22];
    wfWall[37].posA = wfVerts[41]; wfWall[37].posB = wfVerts[42]; wfWall[37].posC = wfVerts[43];
    wfWall[38].posA = wfVerts[41]; wfWall[38].posB = wfVerts[43]; wfWall[38].posC = wfVerts[37];
    wfWall[39].posA = wfVerts[37]; wfWall[39].posB = wfVerts[43]; wfWall[39].posC = wfVerts[38];
    wfWall[40].posA = wfVerts[39]; wfWall[40].posB = wfVerts[44]; wfWall[40].posC = wfVerts[45];
    wfWall[41].posA = wfVerts[39]; wfWall[41].posB = wfVerts[38]; wfWall[41].posC = wfVerts[44];
    wfWall[42].posA = wfVerts[46]; wfWall[42].posB = wfVerts[47]; wfWall[42].posC = wfVerts[48];
    wfWall[43].posA = wfVerts[49]; wfWall[43].posB = wfVerts[48]; wfWall[43].posC = wfVerts[50];
    wfWall[44].posA = wfVerts[49]; wfWall[44].posB = wfVerts[51]; wfWall[44].posC = wfVerts[48];
    wfWall[45].posA = wfVerts[51]; wfWall[45].posB = wfVerts[52]; wfWall[45].posC = wfVerts[48];
    wfWall[46].posA = wfVerts[52]; wfWall[46].posB = wfVerts[46]; wfWall[46].posC = wfVerts[48];
    wfWall[47].posA = wfVerts[53]; wfWall[47].posB = wfVerts[54]; wfWall[47].posC = wfVerts[48];
    wfWall[48].posA = wfVerts[47]; wfWall[48].posB = wfVerts[55]; wfWall[48].posC = wfVerts[48];
    wfWall[49].posA = wfVerts[55]; wfWall[49].posB = wfVerts[56]; wfWall[49].posC = wfVerts[48];
    wfWall[50].posA = wfVerts[56]; wfWall[50].posB = wfVerts[57]; wfWall[50].posC = wfVerts[48];
    wfWall[51].posA = wfVerts[57]; wfWall[51].posB = wfVerts[53]; wfWall[51].posC = wfVerts[48];
    wfWall[52].posA = wfVerts[54]; wfWall[52].posB = wfVerts[58]; wfWall[52].posC = wfVerts[48];
    wfWall[53].posA = wfVerts[50]; wfWall[53].posB = wfVerts[48]; wfWall[53].posC = wfVerts[58];
    wfWall[54].posA = wfVerts[59]; wfWall[54].posB = wfVerts[60]; wfWall[54].posC = wfVerts[61];
    wfWall[55].posA = wfVerts[62]; wfWall[55].posB = wfVerts[61]; wfWall[55].posC = wfVerts[63];
    wfWall[56].posA = wfVerts[62]; wfWall[56].posB = wfVerts[64]; wfWall[56].posC = wfVerts[61];
    wfWall[57].posA = wfVerts[64]; wfWall[57].posB = wfVerts[65]; wfWall[57].posC = wfVerts[61];
    wfWall[58].posA = wfVerts[65]; wfWall[58].posB = wfVerts[59]; wfWall[58].posC = wfVerts[61];
    wfWall[59].posA = wfVerts[66]; wfWall[59].posB = wfVerts[67]; wfWall[59].posC = wfVerts[61];
    wfWall[60].posA = wfVerts[60]; wfWall[60].posB = wfVerts[68]; wfWall[60].posC = wfVerts[61];
    wfWall[61].posA = wfVerts[68]; wfWall[61].posB = wfVerts[69]; wfWall[61].posC = wfVerts[61];
    wfWall[62].posA = wfVerts[69]; wfWall[62].posB = wfVerts[70]; wfWall[62].posC = wfVerts[61];
    wfWall[63].posA = wfVerts[70]; wfWall[63].posB = wfVerts[66]; wfWall[63].posC = wfVerts[61];
    wfWall[64].posA = wfVerts[67]; wfWall[64].posB = wfVerts[71]; wfWall[64].posC = wfVerts[61];
    wfWall[65].posA = wfVerts[63]; wfWall[65].posB = wfVerts[61]; wfWall[65].posC = wfVerts[71];
    wfWall[66].posA = wfVerts[72]; wfWall[66].posB = wfVerts[73]; wfWall[66].posC = wfVerts[74];
    wfWall[67].posA = wfVerts[75]; wfWall[67].posB = wfVerts[74]; wfWall[67].posC = wfVerts[76];
    wfWall[68].posA = wfVerts[75]; wfWall[68].posB = wfVerts[77]; wfWall[68].posC = wfVerts[74];
    wfWall[69].posA = wfVerts[77]; wfWall[69].posB = wfVerts[78]; wfWall[69].posC = wfVerts[74];
    wfWall[70].posA = wfVerts[78]; wfWall[70].posB = wfVerts[72]; wfWall[70].posC = wfVerts[74];
    wfWall[71].posA = wfVerts[79]; wfWall[71].posB = wfVerts[80]; wfWall[71].posC = wfVerts[74];
    wfWall[72].posA = wfVerts[73]; wfWall[72].posB = wfVerts[81]; wfWall[72].posC = wfVerts[74];
    wfWall[73].posA = wfVerts[81]; wfWall[73].posB = wfVerts[82]; wfWall[73].posC = wfVerts[74];
    wfWall[74].posA = wfVerts[82]; wfWall[74].posB = wfVerts[83]; wfWall[74].posC = wfVerts[74];
    wfWall[75].posA = wfVerts[83]; wfWall[75].posB = wfVerts[79]; wfWall[75].posC = wfVerts[74];
    wfWall[76].posA = wfVerts[80]; wfWall[76].posB = wfVerts[84]; wfWall[76].posC = wfVerts[74];
    wfWall[77].posA = wfVerts[76]; wfWall[77].posB = wfVerts[74]; wfWall[77].posC = wfVerts[84];
    wfWall[78].posA = wfVerts[85]; wfWall[78].posB = wfVerts[86]; wfWall[78].posC = wfVerts[87];
    wfWall[79].posA = wfVerts[44]; wfWall[79].posB = wfVerts[88]; wfWall[79].posC = wfVerts[89];
    wfWall[80].posA = wfVerts[44]; wfWall[80].posB = wfVerts[89]; wfWall[80].posC = wfVerts[45];
    wfWall[81].posA = wfVerts[89]; wfWall[81].posB = wfVerts[88]; wfWall[81].posC = wfVerts[90];
    wfWall[82].posA = wfVerts[89]; wfWall[82].posB = wfVerts[90]; wfWall[82].posC = wfVerts[91];
    wfWall[83].posA = wfVerts[87]; wfWall[83].posB = wfVerts[92]; wfWall[83].posC = wfVerts[93];
    wfWall[84].posA = wfVerts[87]; wfWall[84].posB = wfVerts[86]; wfWall[84].posC = wfVerts[92];
    wfWall[85].posA = wfVerts[91]; wfWall[85].posB = wfVerts[94]; wfWall[85].posC = wfVerts[85];
    wfWall[86].posA = wfVerts[85]; wfWall[86].posB = wfVerts[94]; wfWall[86].posC = wfVerts[86];
    wfWall[87].posA = wfVerts[91]; wfWall[87].posB = wfVerts[90]; wfWall[87].posC = wfVerts[94];
    wfWall[88].posA = wfVerts[95]; wfWall[88].posB = wfVerts[96]; wfWall[88].posC = wfVerts[97];
    wfWall[89].posA = wfVerts[98]; wfWall[89].posB = wfVerts[95]; wfWall[89].posC = wfVerts[97];
    wfWall[90].posA = wfVerts[99]; wfWall[90].posB = wfVerts[98]; wfWall[90].posC = wfVerts[97];
    wfWall[91].posA = wfVerts[100]; wfWall[91].posB = wfVerts[99]; wfWall[91].posC = wfVerts[97];
    wfWall[92].posA = wfVerts[101]; wfWall[92].posB = wfVerts[102]; wfWall[92].posC = wfVerts[103];
    wfWall[93].posA = wfVerts[104]; wfWall[93].posB = wfVerts[105]; wfWall[93].posC = wfVerts[106];
    wfWall[94].posA = wfVerts[107]; wfWall[94].posB = wfVerts[105]; wfWall[94].posC = wfVerts[104];
    wfWall[95].posA = wfVerts[108]; wfWall[95].posB = wfVerts[105]; wfWall[95].posC = wfVerts[107];
    wfWall[96].posA = wfVerts[109]; wfWall[96].posB = wfVerts[105]; wfWall[96].posC = wfVerts[108];
    wfWall[97].posA = wfVerts[110]; wfWall[97].posB = wfVerts[105]; wfWall[97].posC = wfVerts[109];
    wfWall[98].posA = wfVerts[105]; wfWall[98].posB = wfVerts[101]; wfWall[98].posC = wfVerts[103];
    wfWall[99].posA = wfVerts[106]; wfWall[99].posB = wfVerts[105]; wfWall[99].posC = wfVerts[103];
    wfWall[100].posA = wfVerts[101]; wfWall[100].posB = wfVerts[105]; wfWall[100].posC = wfVerts[110];
    wfWall[101].posA = wfVerts[102]; wfWall[101].posB = wfVerts[101]; wfWall[101].posC = wfVerts[110];
    wfWall[102].posA = wfVerts[111]; wfWall[102].posB = wfVerts[112]; wfWall[102].posC = wfVerts[113];
    wfWall[103].posA = wfVerts[114]; wfWall[103].posB = wfVerts[115]; wfWall[103].posC = wfVerts[112];
    wfWall[104].posA = wfVerts[114]; wfWall[104].posB = wfVerts[112]; wfWall[104].posC = wfVerts[111];
    wfWall[105].posA = wfVerts[116]; wfWall[105].posB = wfVerts[117]; wfWall[105].posC = wfVerts[115];
    wfWall[106].posA = wfVerts[116]; wfWall[106].posB = wfVerts[115]; wfWall[106].posC = wfVerts[114];
    wfWall[107].posA = wfVerts[118]; wfWall[107].posB = wfVerts[113]; wfWall[107].posC = wfVerts[117];
    wfWall[108].posA = wfVerts[111]; wfWall[108].posB = wfVerts[113]; wfWall[108].posC = wfVerts[118];
    wfWall[109].posA = wfVerts[116]; wfWall[109].posB = wfVerts[114]; wfWall[109].posC = wfVerts[111];
    wfWall[110].posA = wfVerts[116]; wfWall[110].posB = wfVerts[111]; wfWall[110].posC = wfVerts[118];
    wfWall[111].posA = wfVerts[118]; wfWall[111].posB = wfVerts[117]; wfWall[111].posC = wfVerts[116];
    wfWall[112].posA = wfVerts[119]; wfWall[112].posB = wfVerts[120]; wfWall[112].posC = wfVerts[121];
    wfWall[113].posA = wfVerts[121]; wfWall[113].posB = wfVerts[122]; wfWall[113].posC = wfVerts[123];
    wfWall[114].posA = wfVerts[121]; wfWall[114].posB = wfVerts[123]; wfWall[114].posC = wfVerts[119];
    wfWall[115].posA = wfVerts[122]; wfWall[115].posB = wfVerts[124]; wfWall[115].posC = wfVerts[125];
    wfWall[116].posA = wfVerts[122]; wfWall[116].posB = wfVerts[125]; wfWall[116].posC = wfVerts[123];
    wfWall[117].posA = wfVerts[124]; wfWall[117].posB = wfVerts[120]; wfWall[117].posC = wfVerts[126];
    wfWall[118].posA = wfVerts[124]; wfWall[118].posB = wfVerts[126]; wfWall[118].posC = wfVerts[125];
    wfWall[119].posA = wfVerts[123]; wfWall[119].posB = wfVerts[126]; wfWall[119].posC = wfVerts[119];
    wfWall[120].posA = wfVerts[119]; wfWall[120].posB = wfVerts[126]; wfWall[120].posC = wfVerts[120];
    wfWall[121].posA = wfVerts[123]; wfWall[121].posB = wfVerts[125]; wfWall[121].posC = wfVerts[126];
    wfWall[122].posA = wfVerts[127]; wfWall[122].posB = wfVerts[128]; wfWall[122].posC = wfVerts[129];
    wfWall[123].posA = wfVerts[127]; wfWall[123].posB = wfVerts[130]; wfWall[123].posC = wfVerts[128];
    wfWall[124].posA = wfVerts[131]; wfWall[124].posB = wfVerts[132]; wfWall[124].posC = wfVerts[133];
    wfWall[125].posA = wfVerts[127]; wfWall[125].posB = wfVerts[134]; wfWall[125].posC = wfVerts[130];
    wfWall[126].posA = wfVerts[135]; wfWall[126].posB = wfVerts[136]; wfWall[126].posC = wfVerts[137];
    wfWall[127].posA = wfVerts[135]; wfWall[127].posB = wfVerts[138]; wfWall[127].posC = wfVerts[136];
    wfWall[128].posA = wfVerts[139]; wfWall[128].posB = wfVerts[136]; wfWall[128].posC = wfVerts[138];
    wfWall[129].posA = wfVerts[139]; wfWall[129].posB = wfVerts[138]; wfWall[129].posC = wfVerts[140];
    wfWall[130].posA = wfVerts[140]; wfWall[130].posB = wfVerts[141]; wfWall[130].posC = wfVerts[142];
    wfWall[131].posA = wfVerts[140]; wfWall[131].posB = wfVerts[143]; wfWall[131].posC = wfVerts[141];
    wfWall[132].posA = wfVerts[135]; wfWall[132].posB = wfVerts[131]; wfWall[132].posC = wfVerts[144];
    wfWall[133].posA = wfVerts[140]; wfWall[133].posB = wfVerts[145]; wfWall[133].posC = wfVerts[139];
    wfWall[134].posA = wfVerts[144]; wfWall[134].posB = wfVerts[131]; wfWall[134].posC = wfVerts[23];
    wfWall[135].posA = wfVerts[146]; wfWall[135].posB = wfVerts[23]; wfWall[135].posC = wfVerts[131];
    wfWall[136].posA = wfVerts[137]; wfWall[136].posB = wfVerts[131]; wfWall[136].posC = wfVerts[135];
    wfWall[137].posA = wfVerts[133]; wfWall[137].posB = wfVerts[132]; wfWall[137].posC = wfVerts[147];
    wfWall[138].posA = wfVerts[146]; wfWall[138].posB = wfVerts[148]; wfWall[138].posC = wfVerts[149];
    wfWall[139].posA = wfVerts[146]; wfWall[139].posB = wfVerts[149]; wfWall[139].posC = wfVerts[150];
    wfWall[140].posA = wfVerts[151]; wfWall[140].posB = wfVerts[152]; wfWall[140].posC = wfVerts[153];
    wfWall[141].posA = wfVerts[151]; wfWall[141].posB = wfVerts[147]; wfWall[141].posC = wfVerts[152];
    wfWall[142].posA = wfVerts[154]; wfWall[142].posB = wfVerts[149]; wfWall[142].posC = wfVerts[148];
    wfWall[143].posA = wfVerts[133]; wfWall[143].posB = wfVerts[147]; wfWall[143].posC = wfVerts[151];
    wfWall[144].posA = wfVerts[154]; wfWall[144].posB = wfVerts[148]; wfWall[144].posC = wfVerts[155];
    wfWall[145].posA = wfVerts[156]; wfWall[145].posB = wfVerts[157]; wfWall[145].posC = wfVerts[158];
    wfWall[146].posA = wfVerts[154]; wfWall[146].posB = wfVerts[155]; wfWall[146].posC = wfVerts[159];
    wfWall[147].posA = wfVerts[160]; wfWall[147].posB = wfVerts[154]; wfWall[147].posC = wfVerts[159];
    wfWall[148].posA = wfVerts[160]; wfWall[148].posB = wfVerts[159]; wfWall[148].posC = wfVerts[158];
    wfWall[149].posA = wfVerts[157]; wfWall[149].posB = wfVerts[160]; wfWall[149].posC = wfVerts[158];
    wfWall[150].posA = wfVerts[161]; wfWall[150].posB = wfVerts[162]; wfWall[150].posC = wfVerts[156];
    wfWall[151].posA = wfVerts[156]; wfWall[151].posB = wfVerts[162]; wfWall[151].posC = wfVerts[157];
    wfWall[152].posA = wfVerts[161]; wfWall[152].posB = wfVerts[163]; wfWall[152].posC = wfVerts[162];
    wfWall[153].posA = wfVerts[164]; wfWall[153].posB = wfVerts[145]; wfWall[153].posC = wfVerts[165];
    wfWall[154].posA = wfVerts[164]; wfWall[154].posB = wfVerts[165]; wfWall[154].posC = wfVerts[166];
    wfWall[155].posA = wfVerts[167]; wfWall[155].posB = wfVerts[168]; wfWall[155].posC = wfVerts[169];
    wfWall[156].posA = wfVerts[167]; wfWall[156].posB = wfVerts[170]; wfWall[156].posC = wfVerts[168];
    wfWall[157].posA = wfVerts[171]; wfWall[157].posB = wfVerts[172]; wfWall[157].posC = wfVerts[173];
    wfWall[158].posA = wfVerts[174]; wfWall[158].posB = wfVerts[175]; wfWall[158].posC = wfVerts[176];
    wfWall[159].posA = wfVerts[174]; wfWall[159].posB = wfVerts[177]; wfWall[159].posC = wfVerts[175];
    wfWall[160].posA = wfVerts[171]; wfWall[160].posB = wfVerts[173]; wfWall[160].posC = wfVerts[178];
    wfWall[161].posA = wfVerts[179]; wfWall[161].posB = wfVerts[180]; wfWall[161].posC = wfVerts[181];
    wfWall[162].posA = wfVerts[179]; wfWall[162].posB = wfVerts[182]; wfWall[162].posC = wfVerts[180];
    wfWall[163].posA = wfVerts[177]; wfWall[163].posB = wfVerts[174]; wfWall[163].posC = wfVerts[170];
    wfWall[164].posA = wfVerts[170]; wfWall[164].posB = wfVerts[167]; wfWall[164].posC = wfVerts[145];
    wfWall[165].posA = wfVerts[172]; wfWall[165].posB = wfVerts[171]; wfWall[165].posC = wfVerts[177];
    wfWall[166].posA = wfVerts[182]; wfWall[166].posB = wfVerts[179]; wfWall[166].posC = wfVerts[172];
    wfWall[167].posA = wfVerts[183]; wfWall[167].posB = wfVerts[182]; wfWall[167].posC = wfVerts[184];
    wfWall[168].posA = wfVerts[184]; wfWall[168].posB = wfVerts[185]; wfWall[168].posC = wfVerts[183];
    wfWall[169].posA = wfVerts[185]; wfWall[169].posB = wfVerts[186]; wfWall[169].posC = wfVerts[183];
    wfWall[170].posA = wfVerts[187]; wfWall[170].posB = wfVerts[184]; wfWall[170].posC = wfVerts[140];
    wfWall[171].posA = wfVerts[188]; wfWall[171].posB = wfVerts[189]; wfWall[171].posC = wfVerts[190];
    wfWall[172].posA = wfVerts[188]; wfWall[172].posB = wfVerts[190]; wfWall[172].posC = wfVerts[191];
    wfWall[173].posA = wfVerts[192]; wfWall[173].posB = wfVerts[193]; wfWall[173].posC = wfVerts[194];
    wfWall[174].posA = wfVerts[192]; wfWall[174].posB = wfVerts[195]; wfWall[174].posC = wfVerts[193];
    wfWall[175].posA = wfVerts[196]; wfWall[175].posB = wfVerts[195]; wfWall[175].posC = wfVerts[192];
    wfWall[176].posA = wfVerts[196]; wfWall[176].posB = wfVerts[188]; wfWall[176].posC = wfVerts[195];
    wfWall[177].posA = wfVerts[197]; wfWall[177].posB = wfVerts[189]; wfWall[177].posC = wfVerts[198];
    wfWall[178].posA = wfVerts[199]; wfWall[178].posB = wfVerts[197]; wfWall[178].posC = wfVerts[198];
    wfWall[179].posA = wfVerts[200]; wfWall[179].posB = wfVerts[201]; wfWall[179].posC = wfVerts[197];
    wfWall[180].posA = wfVerts[200]; wfWall[180].posB = wfVerts[197]; wfWall[180].posC = wfVerts[199];
    wfWall[181].posA = wfVerts[190]; wfWall[181].posB = wfVerts[189]; wfWall[181].posC = wfVerts[197];
    wfWall[182].posA = wfVerts[193]; wfWall[182].posB = wfVerts[195]; wfWall[182].posC = wfVerts[191];
    wfWall[183].posA = wfVerts[190]; wfWall[183].posB = wfVerts[197]; wfWall[183].posC = wfVerts[201];
    wfWall[184].posA = wfVerts[195]; wfWall[184].posB = wfVerts[188]; wfWall[184].posC = wfVerts[191];
    wfWall[185].posA = wfVerts[202]; wfWall[185].posB = wfVerts[203]; wfWall[185].posC = wfVerts[204];
    wfWall[186].posA = wfVerts[203]; wfWall[186].posB = wfVerts[205]; wfWall[186].posC = wfVerts[206];
    wfWall[187].posA = wfVerts[203]; wfWall[187].posB = wfVerts[206]; wfWall[187].posC = wfVerts[207];
    wfWall[188].posA = wfVerts[208]; wfWall[188].posB = wfVerts[209]; wfWall[188].posC = wfVerts[210];
    wfWall[189].posA = wfVerts[208]; wfWall[189].posB = wfVerts[211]; wfWall[189].posC = wfVerts[209];
    wfWall[190].posA = wfVerts[204]; wfWall[190].posB = wfVerts[211]; wfWall[190].posC = wfVerts[208];
    wfWall[191].posA = wfVerts[204]; wfWall[191].posB = wfVerts[203]; wfWall[191].posC = wfVerts[211];
    wfWall[192].posA = wfVerts[212]; wfWall[192].posB = wfVerts[205]; wfWall[192].posC = wfVerts[202];
    wfWall[193].posA = wfVerts[213]; wfWall[193].posB = wfVerts[212]; wfWall[193].posC = wfVerts[202];
    wfWall[194].posA = wfVerts[214]; wfWall[194].posB = wfVerts[215]; wfWall[194].posC = wfVerts[212];
    wfWall[195].posA = wfVerts[214]; wfWall[195].posB = wfVerts[212]; wfWall[195].posC = wfVerts[213];
    wfWall[196].posA = wfVerts[206]; wfWall[196].posB = wfVerts[205]; wfWall[196].posC = wfVerts[212];
    wfWall[197].posA = wfVerts[209]; wfWall[197].posB = wfVerts[211]; wfWall[197].posC = wfVerts[207];
    wfWall[198].posA = wfVerts[206]; wfWall[198].posB = wfVerts[212]; wfWall[198].posC = wfVerts[215];
    wfWall[199].posA = wfVerts[211]; wfWall[199].posB = wfVerts[203]; wfWall[199].posC = wfVerts[207];
    wfWall[200].posA = wfVerts[216]; wfWall[200].posB = wfVerts[217]; wfWall[200].posC = wfVerts[218];
    wfWall[201].posA = wfVerts[219]; wfWall[201].posB = wfVerts[220]; wfWall[201].posC = wfVerts[221];
    wfWall[202].posA = wfVerts[220]; wfWall[202].posB = wfVerts[222]; wfWall[202].posC = wfVerts[221];
    wfWall[203].posA = wfVerts[223]; wfWall[203].posB = wfVerts[218]; wfWall[203].posC = wfVerts[217];
    wfWall[204].posA = wfVerts[223]; wfWall[204].posB = wfVerts[224]; wfWall[204].posC = wfVerts[218];
    wfWall[205].posA = wfVerts[225]; wfWall[205].posB = wfVerts[222]; wfWall[205].posC = wfVerts[220];
    wfWall[206].posA = wfVerts[216]; wfWall[206].posB = wfVerts[218]; wfWall[206].posC = wfVerts[226];
    wfWall[207].posA = wfVerts[226]; wfWall[207].posB = wfVerts[218]; wfWall[207].posC = wfVerts[227];
    wfWall[208].posA = wfVerts[218]; wfWall[208].posB = wfVerts[224]; wfWall[208].posC = wfVerts[227];
    wfWall[209].posA = wfVerts[225]; wfWall[209].posB = wfVerts[220]; wfWall[209].posC = wfVerts[228];
    wfWall[210].posA = wfVerts[228]; wfWall[210].posB = wfVerts[219]; wfWall[210].posC = wfVerts[229];
    wfWall[211].posA = wfVerts[228]; wfWall[211].posB = wfVerts[220]; wfWall[211].posC = wfVerts[219];
    wfWall[212].posA = wfVerts[222]; wfWall[212].posB = wfVerts[223]; wfWall[212].posC = wfVerts[221];
    wfWall[213].posA = wfVerts[222]; wfWall[213].posB = wfVerts[224]; wfWall[213].posC = wfVerts[223];
    wfWall[214].posA = wfVerts[164]; wfWall[214].posB = wfVerts[230]; wfWall[214].posC = wfVerts[231];
    wfWall[215].posA = wfVerts[230]; wfWall[215].posB = wfVerts[232]; wfWall[215].posC = wfVerts[231];
    wfWall[216].posA = wfVerts[233]; wfWall[216].posB = wfVerts[234]; wfWall[216].posC = wfVerts[235];
    wfWall[217].posA = wfVerts[18]; wfWall[217].posB = wfVerts[13]; wfWall[217].posC = wfVerts[233];
    wfWall[218].posA = wfVerts[153]; wfWall[218].posB = wfVerts[18]; wfWall[218].posC = wfVerts[233];
    wfWall[219].posA = wfVerts[18]; wfWall[219].posB = wfVerts[153]; wfWall[219].posC = wfVerts[152];
    wfWall[220].posA = wfVerts[153]; wfWall[220].posB = wfVerts[233]; wfWall[220].posC = wfVerts[235];
    wfWall[221].posA = wfVerts[236]; wfWall[221].posB = wfVerts[237]; wfWall[221].posC = wfVerts[238];
    wfWall[222].posA = wfVerts[236]; wfWall[222].posB = wfVerts[239]; wfWall[222].posC = wfVerts[237];
    wfWall[223].posA = wfVerts[240]; wfWall[223].posB = wfVerts[241]; wfWall[223].posC = wfVerts[238];
    wfWall[224].posA = wfVerts[242]; wfWall[224].posB = wfVerts[243]; wfWall[224].posC = wfVerts[244];
    wfWall[225].posA = wfVerts[245]; wfWall[225].posB = wfVerts[242]; wfWall[225].posC = wfVerts[244];
    wfWall[226].posA = wfVerts[246]; wfWall[226].posB = wfVerts[247]; wfWall[226].posC = wfVerts[248];
    wfWall[227].posA = wfVerts[247]; wfWall[227].posB = wfVerts[249]; wfWall[227].posC = wfVerts[248];
    wfWall[228].posA = wfVerts[239]; wfWall[228].posB = wfVerts[236]; wfWall[228].posC = wfVerts[250];
    wfWall[229].posA = wfVerts[140]; wfWall[229].posB = wfVerts[251]; wfWall[229].posC = wfVerts[252];
    wfWall[230].posA = wfVerts[140]; wfWall[230].posB = wfVerts[142]; wfWall[230].posC = wfVerts[251];
    wfWall[231].posA = wfVerts[253]; wfWall[231].posB = wfVerts[239]; wfWall[231].posC = wfVerts[250];
    wfWall[232].posA = wfVerts[253]; wfWall[232].posB = wfVerts[254]; wfWall[232].posC = wfVerts[239];
    wfWall[233].posA = wfVerts[253]; wfWall[233].posB = wfVerts[161]; wfWall[233].posC = wfVerts[254];
    wfWall[234].posA = wfVerts[161]; wfWall[234].posB = wfVerts[253]; wfWall[234].posC = wfVerts[163];
    wfWall[235].posA = wfVerts[236]; wfWall[235].posB = wfVerts[255]; wfWall[235].posC = wfVerts[250];
    wfWall[236].posA = wfVerts[256]; wfWall[236].posB = wfVerts[257]; wfWall[236].posC = wfVerts[258];
    wfWall[237].posA = wfVerts[259]; wfWall[237].posB = wfVerts[257]; wfWall[237].posC = wfVerts[256];
    wfWall[238].posA = wfVerts[260]; wfWall[238].posB = wfVerts[238]; wfWall[238].posC = wfVerts[237];
    wfWall[239].posA = wfVerts[260]; wfWall[239].posB = wfVerts[237]; wfWall[239].posC = wfVerts[261];
    wfWall[240].posA = wfVerts[262]; wfWall[240].posB = wfVerts[263]; wfWall[240].posC = wfVerts[264];
    wfWall[241].posA = wfVerts[262]; wfWall[241].posB = wfVerts[265]; wfWall[241].posC = wfVerts[263];
    wfWall[242].posA = wfVerts[260]; wfWall[242].posB = wfVerts[261]; wfWall[242].posC = wfVerts[266];
    wfWall[243].posA = wfVerts[267]; wfWall[243].posB = wfVerts[252]; wfWall[243].posC = wfVerts[251];
    wfWall[244].posA = wfVerts[267]; wfWall[244].posB = wfVerts[251]; wfWall[244].posC = wfVerts[259];
    wfWall[245].posA = wfVerts[259]; wfWall[245].posB = wfVerts[256]; wfWall[245].posC = wfVerts[267];
    wfWall[246].posA = wfVerts[268]; wfWall[246].posB = wfVerts[264]; wfWall[246].posC = wfVerts[263];
    wfWall[247].posA = wfVerts[234]; wfWall[247].posB = wfVerts[240]; wfWall[247].posC = wfVerts[235];
    wfWall[248].posA = wfVerts[261]; wfWall[248].posB = wfVerts[161]; wfWall[248].posC = wfVerts[266];
    wfWall[249].posA = wfVerts[263]; wfWall[249].posB = wfVerts[269]; wfWall[249].posC = wfVerts[268];
    wfWall[250].posA = wfVerts[240]; wfWall[250].posB = wfVerts[153]; wfWall[250].posC = wfVerts[235];
    wfWall[251].posA = wfVerts[270]; wfWall[251].posB = wfVerts[271]; wfWall[251].posC = wfVerts[272];
    wfWall[252].posA = wfVerts[273]; wfWall[252].posB = wfVerts[271]; wfWall[252].posC = wfVerts[270];
    wfWall[253].posA = wfVerts[273]; wfWall[253].posB = wfVerts[265]; wfWall[253].posC = wfVerts[271];
    wfWall[254].posA = wfVerts[265]; wfWall[254].posB = wfVerts[262]; wfWall[254].posC = wfVerts[271];
    wfWall[255].posA = wfVerts[273]; wfWall[255].posB = wfVerts[272]; wfWall[255].posC = wfVerts[17];
    wfWall[256].posA = wfVerts[273]; wfWall[256].posB = wfVerts[270]; wfWall[256].posC = wfVerts[272];
    wfWall[257].posA = wfVerts[272]; wfWall[257].posB = wfVerts[15]; wfWall[257].posC = wfVerts[17];
    wfWall[258].posA = wfVerts[261]; wfWall[258].posB = wfVerts[254]; wfWall[258].posC = wfVerts[161];
    wfWall[259].posA = wfVerts[256]; wfWall[259].posB = wfVerts[258]; wfWall[259].posC = wfVerts[274];
    wfWall[260].posA = wfVerts[275]; wfWall[260].posB = wfVerts[276]; wfWall[260].posC = wfVerts[277];
    wfWall[261].posA = wfVerts[278]; wfWall[261].posB = wfVerts[279]; wfWall[261].posC = wfVerts[280];
    wfWall[262].posA = wfVerts[278]; wfWall[262].posB = wfVerts[281]; wfWall[262].posC = wfVerts[279];
    wfWall[263].posA = wfVerts[282]; wfWall[263].posB = wfVerts[283]; wfWall[263].posC = wfVerts[284];
    wfWall[264].posA = wfVerts[282]; wfWall[264].posB = wfVerts[285]; wfWall[264].posC = wfVerts[283];
    wfWall[265].posA = wfVerts[279]; wfWall[265].posB = wfVerts[285]; wfWall[265].posC = wfVerts[282];
    wfWall[266].posA = wfVerts[279]; wfWall[266].posB = wfVerts[281]; wfWall[266].posC = wfVerts[285];
    wfWall[267].posA = wfVerts[286]; wfWall[267].posB = wfVerts[275]; wfWall[267].posC = wfVerts[277];
    wfWall[268].posA = wfVerts[276]; wfWall[268].posB = wfVerts[287]; wfWall[268].posC = wfVerts[277];
    wfWall[269].posA = wfVerts[276]; wfWall[269].posB = wfVerts[288]; wfWall[269].posC = wfVerts[289];
    wfWall[270].posA = wfVerts[276]; wfWall[270].posB = wfVerts[289]; wfWall[270].posC = wfVerts[287];
    wfWall[271].posA = wfVerts[286]; wfWall[271].posB = wfVerts[290]; wfWall[271].posC = wfVerts[289];
    wfWall[272].posA = wfVerts[288]; wfWall[272].posB = wfVerts[286]; wfWall[272].posC = wfVerts[289];
    wfWall[273].posA = wfVerts[286]; wfWall[273].posB = wfVerts[277]; wfWall[273].posC = wfVerts[290];
    wfWall[274].posA = wfVerts[291]; wfWall[274].posB = wfVerts[292]; wfWall[274].posC = wfVerts[293];
    wfWall[275].posA = wfVerts[294]; wfWall[275].posB = wfVerts[254]; wfWall[275].posC = wfVerts[288];
    wfWall[276].posA = wfVerts[254]; wfWall[276].posB = wfVerts[286]; wfWall[276].posC = wfVerts[288];
    wfWall[277].posA = wfVerts[254]; wfWall[277].posB = wfVerts[275]; wfWall[277].posC = wfVerts[286];
    wfWall[278].posA = wfVerts[254]; wfWall[278].posB = wfVerts[261]; wfWall[278].posC = wfVerts[275];
    wfWall[279].posA = wfVerts[261]; wfWall[279].posB = wfVerts[295]; wfWall[279].posC = wfVerts[276];
    wfWall[280].posA = wfVerts[261]; wfWall[280].posB = wfVerts[276]; wfWall[280].posC = wfVerts[275];
    wfWall[281].posA = wfVerts[295]; wfWall[281].posB = wfVerts[294]; wfWall[281].posC = wfVerts[288];
    wfWall[282].posA = wfVerts[295]; wfWall[282].posB = wfVerts[288]; wfWall[282].posC = wfVerts[276];
    wfWall[283].posA = wfVerts[296]; wfWall[283].posB = wfVerts[297]; wfWall[283].posC = wfVerts[298];
    wfWall[284].posA = wfVerts[296]; wfWall[284].posB = wfVerts[298]; wfWall[284].posC = wfVerts[291];
    wfWall[285].posA = wfVerts[299]; wfWall[285].posB = wfVerts[300]; wfWall[285].posC = wfVerts[301];
    wfWall[286].posA = wfVerts[291]; wfWall[286].posB = wfVerts[298]; wfWall[286].posC = wfVerts[292];
    wfWall[287].posA = wfVerts[293]; wfWall[287].posB = wfVerts[302]; wfWall[287].posC = wfVerts[303];
    wfWall[288].posA = wfVerts[293]; wfWall[288].posB = wfVerts[292]; wfWall[288].posC = wfVerts[302];
    wfWall[289].posA = wfVerts[303]; wfWall[289].posB = wfVerts[302]; wfWall[289].posC = wfVerts[297];
    wfWall[290].posA = wfVerts[303]; wfWall[290].posB = wfVerts[297]; wfWall[290].posC = wfVerts[296];
    wfWall[291].posA = wfVerts[299]; wfWall[291].posB = wfVerts[304]; wfWall[291].posC = wfVerts[300];
    wfWall[292].posA = wfVerts[305]; wfWall[292].posB = wfVerts[306]; wfWall[292].posC = wfVerts[307];
    wfWall[293].posA = wfVerts[301]; wfWall[293].posB = wfVerts[300]; wfWall[293].posC = wfVerts[308];
    wfWall[294].posA = wfVerts[301]; wfWall[294].posB = wfVerts[308]; wfWall[294].posC = wfVerts[309];
    wfWall[295].posA = wfVerts[309]; wfWall[295].posB = wfVerts[310]; wfWall[295].posC = wfVerts[311];
    wfWall[296].posA = wfVerts[309]; wfWall[296].posB = wfVerts[308]; wfWall[296].posC = wfVerts[310];
    wfWall[297].posA = wfVerts[311]; wfWall[297].posB = wfVerts[304]; wfWall[297].posC = wfVerts[299];
    wfWall[298].posA = wfVerts[311]; wfWall[298].posB = wfVerts[310]; wfWall[298].posC = wfVerts[304];
    wfWall[299].posA = wfVerts[312]; wfWall[299].posB = wfVerts[313]; wfWall[299].posC = wfVerts[306];
    wfWall[300].posA = wfVerts[305]; wfWall[300].posB = wfVerts[307]; wfWall[300].posC = wfVerts[314];
    wfWall[301].posA = wfVerts[314]; wfWall[301].posB = wfVerts[307]; wfWall[301].posC = wfVerts[315];
    wfWall[302].posA = wfVerts[314]; wfWall[302].posB = wfVerts[315]; wfWall[302].posC = wfVerts[316];
    wfWall[303].posA = wfVerts[316]; wfWall[303].posB = wfVerts[313]; wfWall[303].posC = wfVerts[312];
    wfWall[304].posA = wfVerts[316]; wfWall[304].posB = wfVerts[315]; wfWall[304].posC = wfVerts[313];
    wfWall[305].posA = wfVerts[312]; wfWall[305].posB = wfVerts[306]; wfWall[305].posC = wfVerts[305];
    wfWall[306].posA = wfVerts[317]; wfWall[306].posB = wfVerts[318]; wfWall[306].posC = wfVerts[319];
    wfWall[307].posA = wfVerts[320]; wfWall[307].posB = wfVerts[319]; wfWall[307].posC = wfVerts[321];
    wfWall[308].posA = wfVerts[320]; wfWall[308].posB = wfVerts[321]; wfWall[308].posC = wfVerts[322];
    wfWall[309].posA = wfVerts[322]; wfWall[309].posB = wfVerts[321]; wfWall[309].posC = wfVerts[323];
    wfWall[310].posA = wfVerts[322]; wfWall[310].posB = wfVerts[323]; wfWall[310].posC = wfVerts[324];
    wfWall[311].posA = wfVerts[324]; wfWall[311].posB = wfVerts[323]; wfWall[311].posC = wfVerts[318];
    wfWall[312].posA = wfVerts[324]; wfWall[312].posB = wfVerts[318]; wfWall[312].posC = wfVerts[317];
    wfWall[313].posA = wfVerts[325]; wfWall[313].posB = wfVerts[326]; wfWall[313].posC = wfVerts[327];
    wfWall[314].posA = wfVerts[317]; wfWall[314].posB = wfVerts[319]; wfWall[314].posC = wfVerts[320];
    wfWall[315].posA = wfVerts[328]; wfWall[315].posB = wfVerts[329]; wfWall[315].posC = wfVerts[238];
    wfWall[316].posA = wfVerts[241]; wfWall[316].posB = wfVerts[328]; wfWall[316].posC = wfVerts[238];
    wfWall[317].posA = wfVerts[261]; wfWall[317].posB = wfVerts[237]; wfWall[317].posC = wfVerts[330];
    wfWall[318].posA = wfVerts[261]; wfWall[318].posB = wfVerts[330]; wfWall[318].posC = wfVerts[295];
    wfWall[319].posA = wfVerts[331]; wfWall[319].posB = wfVerts[325]; wfWall[319].posC = wfVerts[327];
    wfWall[320].posA = wfVerts[294]; wfWall[320].posB = wfVerts[332]; wfWall[320].posC = wfVerts[239];
    wfWall[321].posA = wfVerts[294]; wfWall[321].posB = wfVerts[239]; wfWall[321].posC = wfVerts[254];
    wfWall[322].posA = wfVerts[294]; wfWall[322].posB = wfVerts[295]; wfWall[322].posC = wfVerts[330];
    wfWall[323].posA = wfVerts[332]; wfWall[323].posB = wfVerts[294]; wfWall[323].posC = wfVerts[330];
    wfWall[324].posA = wfVerts[328]; wfWall[324].posB = wfVerts[325]; wfWall[324].posC = wfVerts[329];
    wfWall[325].posA = wfVerts[328]; wfWall[325].posB = wfVerts[326]; wfWall[325].posC = wfVerts[325];
    wfWall[326].posA = wfVerts[333]; wfWall[326].posB = wfVerts[334]; wfWall[326].posC = wfVerts[234];
    wfWall[327].posA = wfVerts[233]; wfWall[327].posB = wfVerts[334]; wfWall[327].posC = wfVerts[333];
    wfWall[328].posA = wfVerts[335]; wfWall[328].posB = wfVerts[336]; wfWall[328].posC = wfVerts[337];
    wfWall[329].posA = wfVerts[337]; wfWall[329].posB = wfVerts[338]; wfWall[329].posC = wfVerts[339];
    wfWall[330].posA = wfVerts[337]; wfWall[330].posB = wfVerts[336]; wfWall[330].posC = wfVerts[338];
    wfWall[331].posA = wfVerts[339]; wfWall[331].posB = wfVerts[338]; wfWall[331].posC = wfVerts[340];
    wfWall[332].posA = wfVerts[339]; wfWall[332].posB = wfVerts[340]; wfWall[332].posC = wfVerts[341];
    wfWall[333].posA = wfVerts[341]; wfWall[333].posB = wfVerts[342]; wfWall[333].posC = wfVerts[335];
    wfWall[334].posA = wfVerts[341]; wfWall[334].posB = wfVerts[340]; wfWall[334].posC = wfVerts[342];
    wfWall[335].posA = wfVerts[336]; wfWall[335].posB = wfVerts[342]; wfWall[335].posC = wfVerts[340];
    wfWall[336].posA = wfVerts[335]; wfWall[336].posB = wfVerts[342]; wfWall[336].posC = wfVerts[336];
    wfWall[337].posA = wfVerts[336]; wfWall[337].posB = wfVerts[340]; wfWall[337].posC = wfVerts[338];
    wfWall[338].posA = wfVerts[343]; wfWall[338].posB = wfVerts[344]; wfWall[338].posC = wfVerts[345];
    wfWall[339].posA = wfVerts[343]; wfWall[339].posB = wfVerts[346]; wfWall[339].posC = wfVerts[344];
    wfWall[340].posA = wfVerts[347]; wfWall[340].posB = wfVerts[346]; wfWall[340].posC = wfVerts[343];
    wfWall[341].posA = wfVerts[347]; wfWall[341].posB = wfVerts[348]; wfWall[341].posC = wfVerts[346];
    wfWall[342].posA = wfVerts[345]; wfWall[342].posB = wfVerts[349]; wfWall[342].posC = wfVerts[350];
    wfWall[343].posA = wfVerts[345]; wfWall[343].posB = wfVerts[344]; wfWall[343].posC = wfVerts[349];
    wfWall[344].posA = wfVerts[351]; wfWall[344].posB = wfVerts[352]; wfWall[344].posC = wfVerts[353];
    wfWall[345].posA = wfVerts[351]; wfWall[345].posB = wfVerts[354]; wfWall[345].posC = wfVerts[352];
    wfWall[346].posA = wfVerts[355]; wfWall[346].posB = wfVerts[354]; wfWall[346].posC = wfVerts[351];
    wfWall[347].posA = wfVerts[355]; wfWall[347].posB = wfVerts[356]; wfWall[347].posC = wfVerts[354];
    wfWall[348].posA = wfVerts[353]; wfWall[348].posB = wfVerts[357]; wfWall[348].posC = wfVerts[358];
    wfWall[349].posA = wfVerts[353]; wfWall[349].posB = wfVerts[352]; wfWall[349].posC = wfVerts[357];
    wfWall[350].posA = wfVerts[359]; wfWall[350].posB = wfVerts[360]; wfWall[350].posC = wfVerts[361];
    wfWall[351].posA = wfVerts[359]; wfWall[351].posB = wfVerts[361]; wfWall[351].posC = wfVerts[362];
    wfWall[352].posA = wfVerts[363]; wfWall[352].posB = wfVerts[364]; wfWall[352].posC = wfVerts[365];
    wfWall[353].posA = wfVerts[363]; wfWall[353].posB = wfVerts[365]; wfWall[353].posC = wfVerts[366];
    wfWall[354].posA = wfVerts[353]; wfWall[354].posB = wfVerts[367]; wfWall[354].posC = wfVerts[368];
    wfWall[355].posA = wfVerts[353]; wfWall[355].posB = wfVerts[368]; wfWall[355].posC = wfVerts[252];
    wfWall[356].posA = wfVerts[369]; wfWall[356].posB = wfVerts[370]; wfWall[356].posC = wfVerts[371];
    wfWall[357].posA = wfVerts[372]; wfWall[357].posB = wfVerts[369]; wfWall[357].posC = wfVerts[371];
    wfWall[358].posA = wfVerts[372]; wfWall[358].posB = wfVerts[371]; wfWall[358].posC = wfVerts[373];
    wfWall[359].posA = wfVerts[374]; wfWall[359].posB = wfVerts[375]; wfWall[359].posC = wfVerts[369];
    wfWall[360].posA = wfVerts[374]; wfWall[360].posB = wfVerts[369]; wfWall[360].posC = wfVerts[372];
    wfWall[361].posA = wfVerts[376]; wfWall[361].posB = wfVerts[370]; wfWall[361].posC = wfVerts[375];
    wfWall[362].posA = wfVerts[376]; wfWall[362].posB = wfVerts[375]; wfWall[362].posC = wfVerts[374];
    wfWall[363].posA = wfVerts[373]; wfWall[363].posB = wfVerts[370]; wfWall[363].posC = wfVerts[376];
    wfWall[364].posA = wfVerts[369]; wfWall[364].posB = wfVerts[375]; wfWall[364].posC = wfVerts[370];
    wfWall[365].posA = wfVerts[373]; wfWall[365].posB = wfVerts[371]; wfWall[365].posC = wfVerts[370];
    wfWall[366].posA = wfVerts[377]; wfWall[366].posB = wfVerts[378]; wfWall[366].posC = wfVerts[272];
    wfWall[367].posA = wfVerts[377]; wfWall[367].posB = wfVerts[271]; wfWall[367].posC = wfVerts[378];
    wfWall[368].posA = wfVerts[379]; wfWall[368].posB = wfVerts[380]; wfWall[368].posC = wfVerts[381];
    wfWall[369].posA = wfVerts[382]; wfWall[369].posB = wfVerts[383]; wfWall[369].posC = wfVerts[384];
    wfWall[370].posA = wfVerts[382]; wfWall[370].posB = wfVerts[384]; wfWall[370].posC = wfVerts[385];
    wfWall[371].posA = wfVerts[386]; wfWall[371].posB = wfVerts[381]; wfWall[371].posC = wfVerts[383];
    wfWall[372].posA = wfVerts[386]; wfWall[372].posB = wfVerts[387]; wfWall[372].posC = wfVerts[381];
    wfWall[373].posA = wfVerts[381]; wfWall[373].posB = wfVerts[380]; wfWall[373].posC = wfVerts[383];
    wfWall[374].posA = wfVerts[379]; wfWall[374].posB = wfVerts[388]; wfWall[374].posC = wfVerts[380];
    wfWall[375].posA = wfVerts[389]; wfWall[375].posB = wfVerts[390]; wfWall[375].posC = wfVerts[391];
    wfWall[376].posA = wfVerts[392]; wfWall[376].posB = wfVerts[393]; wfWall[376].posC = wfVerts[388];
    wfWall[377].posA = wfVerts[392]; wfWall[377].posB = wfVerts[388]; wfWall[377].posC = wfVerts[379];
    wfWall[378].posA = wfVerts[394]; wfWall[378].posB = wfVerts[393]; wfWall[378].posC = wfVerts[392];
    wfWall[379].posA = wfVerts[394]; wfWall[379].posB = wfVerts[395]; wfWall[379].posC = wfVerts[393];
    wfWall[380].posA = wfVerts[396]; wfWall[380].posB = wfVerts[391]; wfWall[380].posC = wfVerts[395];
    wfWall[381].posA = wfVerts[396]; wfWall[381].posB = wfVerts[395]; wfWall[381].posC = wfVerts[394];
    wfWall[382].posA = wfVerts[386]; wfWall[382].posB = wfVerts[397]; wfWall[382].posC = wfVerts[387];
    wfWall[383].posA = wfVerts[389]; wfWall[383].posB = wfVerts[391]; wfWall[383].posC = wfVerts[396];
    wfWall[384].posA = wfVerts[385]; wfWall[384].posB = wfVerts[384]; wfWall[384].posC = wfVerts[390];
    wfWall[385].posA = wfVerts[385]; wfWall[385].posB = wfVerts[390]; wfWall[385].posC = wfVerts[389];
    wfWall[386].posA = wfVerts[398]; wfWall[386].posB = wfVerts[386]; wfWall[386].posC = wfVerts[383];
    wfWall[387].posA = wfVerts[383]; wfWall[387].posB = wfVerts[399]; wfWall[387].posC = wfVerts[398];
    wfWall[388].posA = wfVerts[383]; wfWall[388].posB = wfVerts[382]; wfWall[388].posC = wfVerts[399];
    wfWall[389].posA = wfVerts[400]; wfWall[389].posB = wfVerts[397]; wfWall[389].posC = wfVerts[401];
    wfWall[390].posA = wfVerts[386]; wfWall[390].posB = wfVerts[401]; wfWall[390].posC = wfVerts[397];
    wfWall[391].posA = wfVerts[398]; wfWall[391].posB = wfVerts[401]; wfWall[391].posC = wfVerts[386];
    wfWall[392].posA = wfVerts[398]; wfWall[392].posB = wfVerts[402]; wfWall[392].posC = wfVerts[401];
    wfWall[393].posA = wfVerts[399]; wfWall[393].posB = wfVerts[400]; wfWall[393].posC = wfVerts[402];
    wfWall[394].posA = wfVerts[399]; wfWall[394].posB = wfVerts[402]; wfWall[394].posC = wfVerts[398];
    wfWall[395].posA = wfVerts[400]; wfWall[395].posB = wfVerts[401]; wfWall[395].posC = wfVerts[402];
    wfWall[396].posA = wfVerts[403]; wfWall[396].posB = wfVerts[404]; wfWall[396].posC = wfVerts[405];
    wfWall[397].posA = wfVerts[403]; wfWall[397].posB = wfVerts[405]; wfWall[397].posC = wfVerts[406];
    wfWall[398].posA = wfVerts[406]; wfWall[398].posB = wfVerts[407]; wfWall[398].posC = wfVerts[408];
    wfWall[399].posA = wfVerts[406]; wfWall[399].posB = wfVerts[405]; wfWall[399].posC = wfVerts[407];
    wfWall[400].posA = wfVerts[408]; wfWall[400].posB = wfVerts[409]; wfWall[400].posC = wfVerts[410];
    wfWall[401].posA = wfVerts[408]; wfWall[401].posB = wfVerts[407]; wfWall[401].posC = wfVerts[409];
    wfWall[402].posA = wfVerts[407]; wfWall[402].posB = wfVerts[405]; wfWall[402].posC = wfVerts[404];
    wfWall[403].posA = wfVerts[407]; wfWall[403].posB = wfVerts[404]; wfWall[403].posC = wfVerts[409];
    wfWall[404].posA = wfVerts[411]; wfWall[404].posB = wfVerts[412]; wfWall[404].posC = wfVerts[413];
    wfWall[405].posA = wfVerts[411]; wfWall[405].posB = wfVerts[413]; wfWall[405].posC = wfVerts[414];
    wfWall[406].posA = wfVerts[414]; wfWall[406].posB = wfVerts[415]; wfWall[406].posC = wfVerts[416];
    wfWall[407].posA = wfVerts[414]; wfWall[407].posB = wfVerts[413]; wfWall[407].posC = wfVerts[415];
    wfWall[408].posA = wfVerts[416]; wfWall[408].posB = wfVerts[417]; wfWall[408].posC = wfVerts[418];
    wfWall[409].posA = wfVerts[416]; wfWall[409].posB = wfVerts[415]; wfWall[409].posC = wfVerts[417];
    wfWall[410].posA = wfVerts[415]; wfWall[410].posB = wfVerts[413]; wfWall[410].posC = wfVerts[412];
    wfWall[411].posA = wfVerts[415]; wfWall[411].posB = wfVerts[412]; wfWall[411].posC = wfVerts[417];
    wfWall[412].posA = wfVerts[419]; wfWall[412].posB = wfVerts[420]; wfWall[412].posC = wfVerts[421];
    wfWall[413].posA = wfVerts[419]; wfWall[413].posB = wfVerts[421]; wfWall[413].posC = wfVerts[422];
    wfWall[414].posA = wfVerts[422]; wfWall[414].posB = wfVerts[423]; wfWall[414].posC = wfVerts[424];
    wfWall[415].posA = wfVerts[422]; wfWall[415].posB = wfVerts[421]; wfWall[415].posC = wfVerts[423];
    wfWall[416].posA = wfVerts[424]; wfWall[416].posB = wfVerts[425]; wfWall[416].posC = wfVerts[426];
    wfWall[417].posA = wfVerts[424]; wfWall[417].posB = wfVerts[423]; wfWall[417].posC = wfVerts[425];
    wfWall[418].posA = wfVerts[423]; wfWall[418].posB = wfVerts[421]; wfWall[418].posC = wfVerts[420];
    wfWall[419].posA = wfVerts[423]; wfWall[419].posB = wfVerts[420]; wfWall[419].posC = wfVerts[425];
    wfWall[420].posA = wfVerts[427]; wfWall[420].posB = wfVerts[428]; wfWall[420].posC = wfVerts[429];
    wfWall[421].posA = wfVerts[427]; wfWall[421].posB = wfVerts[429]; wfWall[421].posC = wfVerts[430];
    wfWall[422].posA = wfVerts[430]; wfWall[422].posB = wfVerts[431]; wfWall[422].posC = wfVerts[432];
    wfWall[423].posA = wfVerts[430]; wfWall[423].posB = wfVerts[429]; wfWall[423].posC = wfVerts[431];
    wfWall[424].posA = wfVerts[432]; wfWall[424].posB = wfVerts[433]; wfWall[424].posC = wfVerts[434];
    wfWall[425].posA = wfVerts[432]; wfWall[425].posB = wfVerts[431]; wfWall[425].posC = wfVerts[433];
    wfWall[426].posA = wfVerts[431]; wfWall[426].posB = wfVerts[429]; wfWall[426].posC = wfVerts[428];
    wfWall[427].posA = wfVerts[431]; wfWall[427].posB = wfVerts[428]; wfWall[427].posC = wfVerts[433];
    wfWall[428].posA = wfVerts[435]; wfWall[428].posB = wfVerts[436]; wfWall[428].posC = wfVerts[437];
    wfWall[429].posA = wfVerts[435]; wfWall[429].posB = wfVerts[437]; wfWall[429].posC = wfVerts[438];
    wfWall[430].posA = wfVerts[438]; wfWall[430].posB = wfVerts[439]; wfWall[430].posC = wfVerts[440];
    wfWall[431].posA = wfVerts[438]; wfWall[431].posB = wfVerts[437]; wfWall[431].posC = wfVerts[439];
    wfWall[432].posA = wfVerts[440]; wfWall[432].posB = wfVerts[441]; wfWall[432].posC = wfVerts[442];
    wfWall[433].posA = wfVerts[440]; wfWall[433].posB = wfVerts[439]; wfWall[433].posC = wfVerts[441];
    wfWall[434].posA = wfVerts[439]; wfWall[434].posB = wfVerts[437]; wfWall[434].posC = wfVerts[436];
    wfWall[435].posA = wfVerts[439]; wfWall[435].posB = wfVerts[436]; wfWall[435].posC = wfVerts[441];
    wfWall[436].posA = wfVerts[443]; wfWall[436].posB = wfVerts[444]; wfWall[436].posC = wfVerts[445];
    wfWall[437].posA = wfVerts[443]; wfWall[437].posB = wfVerts[445]; wfWall[437].posC = wfVerts[446];
    wfWall[438].posA = wfVerts[446]; wfWall[438].posB = wfVerts[447]; wfWall[438].posC = wfVerts[448];
    wfWall[439].posA = wfVerts[446]; wfWall[439].posB = wfVerts[445]; wfWall[439].posC = wfVerts[447];
    wfWall[440].posA = wfVerts[448]; wfWall[440].posB = wfVerts[449]; wfWall[440].posC = wfVerts[450];
    wfWall[441].posA = wfVerts[448]; wfWall[441].posB = wfVerts[447]; wfWall[441].posC = wfVerts[449];
    wfWall[442].posA = wfVerts[447]; wfWall[442].posB = wfVerts[445]; wfWall[442].posC = wfVerts[444];
    wfWall[443].posA = wfVerts[447]; wfWall[443].posB = wfVerts[444]; wfWall[443].posC = wfVerts[449];
    wfWall[444].posA = wfVerts[451]; wfWall[444].posB = wfVerts[452]; wfWall[444].posC = wfVerts[453];
    wfWall[445].posA = wfVerts[451]; wfWall[445].posB = wfVerts[453]; wfWall[445].posC = wfVerts[454];
    wfWall[446].posA = wfVerts[454]; wfWall[446].posB = wfVerts[455]; wfWall[446].posC = wfVerts[456];
    wfWall[447].posA = wfVerts[454]; wfWall[447].posB = wfVerts[453]; wfWall[447].posC = wfVerts[455];
    wfWall[448].posA = wfVerts[456]; wfWall[448].posB = wfVerts[457]; wfWall[448].posC = wfVerts[458];
    wfWall[449].posA = wfVerts[456]; wfWall[449].posB = wfVerts[455]; wfWall[449].posC = wfVerts[457];
    wfWall[450].posA = wfVerts[455]; wfWall[450].posB = wfVerts[453]; wfWall[450].posC = wfVerts[452];
    wfWall[451].posA = wfVerts[455]; wfWall[451].posB = wfVerts[452]; wfWall[451].posC = wfVerts[457];
    wfWall[452].posA = wfVerts[459]; wfWall[452].posB = wfVerts[460]; wfWall[452].posC = wfVerts[461];
    wfWall[453].posA = wfVerts[459]; wfWall[453].posB = wfVerts[461]; wfWall[453].posC = wfVerts[462];
    wfWall[454].posA = wfVerts[462]; wfWall[454].posB = wfVerts[463]; wfWall[454].posC = wfVerts[464];
    wfWall[455].posA = wfVerts[462]; wfWall[455].posB = wfVerts[461]; wfWall[455].posC = wfVerts[463];
    wfWall[456].posA = wfVerts[464]; wfWall[456].posB = wfVerts[465]; wfWall[456].posC = wfVerts[466];
    wfWall[457].posA = wfVerts[464]; wfWall[457].posB = wfVerts[463]; wfWall[457].posC = wfVerts[465];
    wfWall[458].posA = wfVerts[463]; wfWall[458].posB = wfVerts[461]; wfWall[458].posC = wfVerts[460];
    wfWall[459].posA = wfVerts[463]; wfWall[459].posB = wfVerts[460]; wfWall[459].posC = wfVerts[465];
    wfWall[460].posA = wfVerts[285]; wfWall[460].posB = wfVerts[278]; wfWall[460].posC = wfVerts[283];
    wfWall[461].posA = wfVerts[285]; wfWall[461].posB = wfVerts[281]; wfWall[461].posC = wfVerts[278];
    wfWall[462].posA = wfVerts[325]; wfWall[462].posB = wfVerts[331]; wfWall[462].posC = wfVerts[238];
    wfWall[463].posA = wfVerts[325]; wfWall[463].posB = wfVerts[238]; wfWall[463].posC = wfVerts[329];
    wfWall[464].posA = wfVerts[467]; wfWall[464].posB = wfVerts[384]; wfWall[464].posC = wfVerts[383];
    wfWall[465].posA = wfVerts[468]; wfWall[465].posB = wfVerts[395]; wfWall[465].posC = wfVerts[469];
    wfWall[466].posA = wfVerts[468]; wfWall[466].posB = wfVerts[393]; wfWall[466].posC = wfVerts[395];
    wfWall[467].posA = wfVerts[469]; wfWall[467].posB = wfVerts[395]; wfWall[467].posC = wfVerts[391];
    wfWall[468].posA = wfVerts[469]; wfWall[468].posB = wfVerts[391]; wfWall[468].posC = wfVerts[470];
    wfWall[469].posA = wfVerts[470]; wfWall[469].posB = wfVerts[390]; wfWall[469].posC = wfVerts[471];
    wfWall[470].posA = wfVerts[470]; wfWall[470].posB = wfVerts[391]; wfWall[470].posC = wfVerts[390];
    wfWall[471].posA = wfVerts[472]; wfWall[471].posB = wfVerts[393]; wfWall[471].posC = wfVerts[468];
    wfWall[472].posA = wfVerts[467]; wfWall[472].posB = wfVerts[383]; wfWall[472].posC = wfVerts[473];
    wfWall[473].posA = wfVerts[473]; wfWall[473].posB = wfVerts[383]; wfWall[473].posC = wfVerts[380];
    wfWall[474].posA = wfVerts[473]; wfWall[474].posB = wfVerts[380]; wfWall[474].posC = wfVerts[474];
    wfWall[475].posA = wfVerts[474]; wfWall[475].posB = wfVerts[380]; wfWall[475].posC = wfVerts[388];
    wfWall[476].posA = wfVerts[474]; wfWall[476].posB = wfVerts[388]; wfWall[476].posC = wfVerts[472];
    wfWall[477].posA = wfVerts[472]; wfWall[477].posB = wfVerts[388]; wfWall[477].posC = wfVerts[393];
    wfWall[478].posA = wfVerts[475]; wfWall[478].posB = wfVerts[476]; wfWall[478].posC = wfVerts[477];
    wfWall[479].posA = wfVerts[475]; wfWall[479].posB = wfVerts[478]; wfWall[479].posC = wfVerts[476];
    wfWall[480].posA = wfVerts[479]; wfWall[480].posB = wfVerts[480]; wfWall[480].posC = wfVerts[481];
    wfWall[481].posA = wfVerts[482]; wfWall[481].posB = wfVerts[483]; wfWall[481].posC = wfVerts[478];
    wfWall[482].posA = wfVerts[482]; wfWall[482].posB = wfVerts[478]; wfWall[482].posC = wfVerts[475];
    wfWall[483].posA = wfVerts[484]; wfWall[483].posB = wfVerts[483]; wfWall[483].posC = wfVerts[482];
    wfWall[484].posA = wfVerts[484]; wfWall[484].posB = wfVerts[485]; wfWall[484].posC = wfVerts[483];
    wfWall[485].posA = wfVerts[481]; wfWall[485].posB = wfVerts[485]; wfWall[485].posC = wfVerts[484];
    wfWall[486].posA = wfVerts[481]; wfWall[486].posB = wfVerts[480]; wfWall[486].posC = wfVerts[485];
    wfWall[487].posA = wfVerts[477]; wfWall[487].posB = wfVerts[486]; wfWall[487].posC = wfVerts[487];
    wfWall[488].posA = wfVerts[479]; wfWall[488].posB = wfVerts[488]; wfWall[488].posC = wfVerts[480];
    wfWall[489].posA = wfVerts[489]; wfWall[489].posB = wfVerts[488]; wfWall[489].posC = wfVerts[479];
    wfWall[490].posA = wfVerts[489]; wfWall[490].posB = wfVerts[490]; wfWall[490].posC = wfVerts[488];
    wfWall[491].posA = wfVerts[487]; wfWall[491].posB = wfVerts[490]; wfWall[491].posC = wfVerts[489];
    wfWall[492].posA = wfVerts[487]; wfWall[492].posB = wfVerts[486]; wfWall[492].posC = wfVerts[490];
    wfWall[493].posA = wfVerts[477]; wfWall[493].posB = wfVerts[476]; wfWall[493].posC = wfVerts[486];
    wfWall[494].posA = wfVerts[471]; wfWall[494].posB = wfVerts[384]; wfWall[494].posC = wfVerts[467];
    wfWall[495].posA = wfVerts[471]; wfWall[495].posB = wfVerts[390]; wfWall[495].posC = wfVerts[384];
    wfWall[496].posA = wfVerts[491]; wfWall[496].posB = wfVerts[492]; wfWall[496].posC = wfVerts[493];
    wfWall[497].posA = wfVerts[494]; wfWall[497].posB = wfVerts[495]; wfWall[497].posC = wfVerts[492];
    wfWall[498].posA = wfVerts[491]; wfWall[498].posB = wfVerts[494]; wfWall[498].posC = wfVerts[492];
    wfWall[499].posA = wfVerts[496]; wfWall[499].posB = wfVerts[497]; wfWall[499].posC = wfVerts[498];
    wfWall[500].posA = wfVerts[496]; wfWall[500].posB = wfVerts[499]; wfWall[500].posC = wfVerts[497];
    wfWall[501].posA = wfVerts[500]; wfWall[501].posB = wfVerts[501]; wfWall[501].posC = wfVerts[499];
    wfWall[502].posA = wfVerts[500]; wfWall[502].posB = wfVerts[499]; wfWall[502].posC = wfVerts[496];
    wfWall[503].posA = wfVerts[502]; wfWall[503].posB = wfVerts[501]; wfWall[503].posC = wfVerts[500];
    wfWall[504].posA = wfVerts[502]; wfWall[504].posB = wfVerts[503]; wfWall[504].posC = wfVerts[501];
    wfWall[505].posA = wfVerts[498]; wfWall[505].posB = wfVerts[497]; wfWall[505].posC = wfVerts[503];
    wfWall[506].posA = wfVerts[498]; wfWall[506].posB = wfVerts[503]; wfWall[506].posC = wfVerts[502];
    wfWall[507].posA = wfVerts[504]; wfWall[507].posB = wfVerts[505]; wfWall[507].posC = wfVerts[506];
    wfWall[508].posA = wfVerts[506]; wfWall[508].posB = wfVerts[505]; wfWall[508].posC = wfVerts[507];
    wfWall[509].posA = wfVerts[506]; wfWall[509].posB = wfVerts[507]; wfWall[509].posC = wfVerts[508];
    wfWall[510].posA = wfVerts[507]; wfWall[510].posB = wfVerts[505]; wfWall[510].posC = wfVerts[509];
    wfWall[511].posA = wfVerts[507]; wfWall[511].posB = wfVerts[509]; wfWall[511].posC = wfVerts[510];
    wfWall[512].posA = wfVerts[511]; wfWall[512].posB = wfVerts[506]; wfWall[512].posC = wfVerts[508];
    wfWall[513].posA = wfVerts[504]; wfWall[513].posB = wfVerts[509]; wfWall[513].posC = wfVerts[505];
    wfWall[514].posA = wfVerts[509]; wfWall[514].posB = wfVerts[504]; wfWall[514].posC = wfVerts[511];
    wfWall[515].posA = wfVerts[509]; wfWall[515].posB = wfVerts[511]; wfWall[515].posC = wfVerts[510];
    wfWall[516].posA = wfVerts[511]; wfWall[516].posB = wfVerts[504]; wfWall[516].posC = wfVerts[506];
    wfWall[517].posA = wfVerts[512]; wfWall[517].posB = wfVerts[513]; wfWall[517].posC = wfVerts[514];
    wfWall[518].posA = wfVerts[514]; wfWall[518].posB = wfVerts[513]; wfWall[518].posC = wfVerts[515];
    wfWall[519].posA = wfVerts[514]; wfWall[519].posB = wfVerts[515]; wfWall[519].posC = wfVerts[516];
    wfWall[520].posA = wfVerts[515]; wfWall[520].posB = wfVerts[513]; wfWall[520].posC = wfVerts[517];
    wfWall[521].posA = wfVerts[515]; wfWall[521].posB = wfVerts[517]; wfWall[521].posC = wfVerts[518];
    wfWall[522].posA = wfVerts[519]; wfWall[522].posB = wfVerts[514]; wfWall[522].posC = wfVerts[516];
    wfWall[523].posA = wfVerts[512]; wfWall[523].posB = wfVerts[517]; wfWall[523].posC = wfVerts[513];
    wfWall[524].posA = wfVerts[517]; wfWall[524].posB = wfVerts[512]; wfWall[524].posC = wfVerts[519];
    wfWall[525].posA = wfVerts[517]; wfWall[525].posB = wfVerts[519]; wfWall[525].posC = wfVerts[518];
    wfWall[526].posA = wfVerts[519]; wfWall[526].posB = wfVerts[512]; wfWall[526].posC = wfVerts[514];
    wfWall[527].posA = wfVerts[517]; wfWall[527].posB = wfVerts[520]; wfWall[527].posC = wfVerts[513];
    wfWall[528].posA = wfVerts[513]; wfWall[528].posB = wfVerts[520]; wfWall[528].posC = wfVerts[521];
    wfWall[529].posA = wfVerts[513]; wfWall[529].posB = wfVerts[521]; wfWall[529].posC = wfVerts[515];
    wfWall[530].posA = wfVerts[521]; wfWall[530].posB = wfVerts[520]; wfWall[530].posC = wfVerts[522];
    wfWall[531].posA = wfVerts[521]; wfWall[531].posB = wfVerts[522]; wfWall[531].posC = wfVerts[523];
    wfWall[532].posA = wfVerts[518]; wfWall[532].posB = wfVerts[513]; wfWall[532].posC = wfVerts[515];
    wfWall[533].posA = wfVerts[517]; wfWall[533].posB = wfVerts[522]; wfWall[533].posC = wfVerts[520];
    wfWall[534].posA = wfVerts[522]; wfWall[534].posB = wfVerts[517]; wfWall[534].posC = wfVerts[518];
    wfWall[535].posA = wfVerts[522]; wfWall[535].posB = wfVerts[518]; wfWall[535].posC = wfVerts[523];
    wfWall[536].posA = wfVerts[518]; wfWall[536].posB = wfVerts[517]; wfWall[536].posC = wfVerts[513];
    wfWall[537].posA = wfVerts[522]; wfWall[537].posB = wfVerts[524]; wfWall[537].posC = wfVerts[520];
    wfWall[538].posA = wfVerts[520]; wfWall[538].posB = wfVerts[524]; wfWall[538].posC = wfVerts[525];
    wfWall[539].posA = wfVerts[520]; wfWall[539].posB = wfVerts[525]; wfWall[539].posC = wfVerts[521];
    wfWall[540].posA = wfVerts[525]; wfWall[540].posB = wfVerts[524]; wfWall[540].posC = wfVerts[526];
    wfWall[541].posA = wfVerts[525]; wfWall[541].posB = wfVerts[526]; wfWall[541].posC = wfVerts[527];
    wfWall[542].posA = wfVerts[523]; wfWall[542].posB = wfVerts[520]; wfWall[542].posC = wfVerts[521];
    wfWall[543].posA = wfVerts[522]; wfWall[543].posB = wfVerts[526]; wfWall[543].posC = wfVerts[524];
    wfWall[544].posA = wfVerts[526]; wfWall[544].posB = wfVerts[522]; wfWall[544].posC = wfVerts[523];
    wfWall[545].posA = wfVerts[526]; wfWall[545].posB = wfVerts[523]; wfWall[545].posC = wfVerts[527];
    wfWall[546].posA = wfVerts[523]; wfWall[546].posB = wfVerts[522]; wfWall[546].posC = wfVerts[520];
    wfWall[547].posA = wfVerts[526]; wfWall[547].posB = wfVerts[528]; wfWall[547].posC = wfVerts[524];
    wfWall[548].posA = wfVerts[524]; wfWall[548].posB = wfVerts[528]; wfWall[548].posC = wfVerts[529];
    wfWall[549].posA = wfVerts[524]; wfWall[549].posB = wfVerts[529]; wfWall[549].posC = wfVerts[525];
    wfWall[550].posA = wfVerts[529]; wfWall[550].posB = wfVerts[528]; wfWall[550].posC = wfVerts[530];
    wfWall[551].posA = wfVerts[529]; wfWall[551].posB = wfVerts[530]; wfWall[551].posC = wfVerts[531];
    wfWall[552].posA = wfVerts[527]; wfWall[552].posB = wfVerts[524]; wfWall[552].posC = wfVerts[525];
    wfWall[553].posA = wfVerts[526]; wfWall[553].posB = wfVerts[530]; wfWall[553].posC = wfVerts[528];
    wfWall[554].posA = wfVerts[530]; wfWall[554].posB = wfVerts[526]; wfWall[554].posC = wfVerts[527];
    wfWall[555].posA = wfVerts[530]; wfWall[555].posB = wfVerts[527]; wfWall[555].posC = wfVerts[531];
    wfWall[556].posA = wfVerts[527]; wfWall[556].posB = wfVerts[526]; wfWall[556].posC = wfVerts[524];
    wfWall[557].posA = wfVerts[532]; wfWall[557].posB = wfVerts[533]; wfWall[557].posC = wfVerts[534];
    wfWall[558].posA = wfVerts[534]; wfWall[558].posB = wfVerts[533]; wfWall[558].posC = wfVerts[535];
    wfWall[559].posA = wfVerts[534]; wfWall[559].posB = wfVerts[535]; wfWall[559].posC = wfVerts[536];
    wfWall[560].posA = wfVerts[535]; wfWall[560].posB = wfVerts[533]; wfWall[560].posC = wfVerts[537];
    wfWall[561].posA = wfVerts[535]; wfWall[561].posB = wfVerts[537]; wfWall[561].posC = wfVerts[538];
    wfWall[562].posA = wfVerts[539]; wfWall[562].posB = wfVerts[534]; wfWall[562].posC = wfVerts[536];
    wfWall[563].posA = wfVerts[532]; wfWall[563].posB = wfVerts[537]; wfWall[563].posC = wfVerts[533];
    wfWall[564].posA = wfVerts[537]; wfWall[564].posB = wfVerts[532]; wfWall[564].posC = wfVerts[539];
    wfWall[565].posA = wfVerts[537]; wfWall[565].posB = wfVerts[539]; wfWall[565].posC = wfVerts[538];
    wfWall[566].posA = wfVerts[539]; wfWall[566].posB = wfVerts[532]; wfWall[566].posC = wfVerts[534];
    wfWall[567].posA = wfVerts[537]; wfWall[567].posB = wfVerts[540]; wfWall[567].posC = wfVerts[533];
    wfWall[568].posA = wfVerts[533]; wfWall[568].posB = wfVerts[540]; wfWall[568].posC = wfVerts[541];
    wfWall[569].posA = wfVerts[533]; wfWall[569].posB = wfVerts[541]; wfWall[569].posC = wfVerts[535];
    wfWall[570].posA = wfVerts[541]; wfWall[570].posB = wfVerts[540]; wfWall[570].posC = wfVerts[542];
    wfWall[571].posA = wfVerts[541]; wfWall[571].posB = wfVerts[542]; wfWall[571].posC = wfVerts[543];
    wfWall[572].posA = wfVerts[538]; wfWall[572].posB = wfVerts[533]; wfWall[572].posC = wfVerts[535];
    wfWall[573].posA = wfVerts[537]; wfWall[573].posB = wfVerts[542]; wfWall[573].posC = wfVerts[540];
    wfWall[574].posA = wfVerts[542]; wfWall[574].posB = wfVerts[537]; wfWall[574].posC = wfVerts[538];
    wfWall[575].posA = wfVerts[542]; wfWall[575].posB = wfVerts[538]; wfWall[575].posC = wfVerts[543];
    wfWall[576].posA = wfVerts[538]; wfWall[576].posB = wfVerts[537]; wfWall[576].posC = wfVerts[533];
    wfWall[577].posA = wfVerts[542]; wfWall[577].posB = wfVerts[544]; wfWall[577].posC = wfVerts[540];
    wfWall[578].posA = wfVerts[540]; wfWall[578].posB = wfVerts[544]; wfWall[578].posC = wfVerts[545];
    wfWall[579].posA = wfVerts[540]; wfWall[579].posB = wfVerts[545]; wfWall[579].posC = wfVerts[541];
    wfWall[580].posA = wfVerts[545]; wfWall[580].posB = wfVerts[544]; wfWall[580].posC = wfVerts[546];
    wfWall[581].posA = wfVerts[545]; wfWall[581].posB = wfVerts[546]; wfWall[581].posC = wfVerts[547];
    wfWall[582].posA = wfVerts[543]; wfWall[582].posB = wfVerts[540]; wfWall[582].posC = wfVerts[541];
    wfWall[583].posA = wfVerts[542]; wfWall[583].posB = wfVerts[546]; wfWall[583].posC = wfVerts[544];
    wfWall[584].posA = wfVerts[546]; wfWall[584].posB = wfVerts[542]; wfWall[584].posC = wfVerts[543];
    wfWall[585].posA = wfVerts[546]; wfWall[585].posB = wfVerts[543]; wfWall[585].posC = wfVerts[547];
    wfWall[586].posA = wfVerts[543]; wfWall[586].posB = wfVerts[542]; wfWall[586].posC = wfVerts[540];
    wfWall[587].posA = wfVerts[546]; wfWall[587].posB = wfVerts[548]; wfWall[587].posC = wfVerts[544];
    wfWall[588].posA = wfVerts[544]; wfWall[588].posB = wfVerts[548]; wfWall[588].posC = wfVerts[549];
    wfWall[589].posA = wfVerts[544]; wfWall[589].posB = wfVerts[549]; wfWall[589].posC = wfVerts[545];
    wfWall[590].posA = wfVerts[549]; wfWall[590].posB = wfVerts[548]; wfWall[590].posC = wfVerts[550];
    wfWall[591].posA = wfVerts[549]; wfWall[591].posB = wfVerts[550]; wfWall[591].posC = wfVerts[551];
    wfWall[592].posA = wfVerts[547]; wfWall[592].posB = wfVerts[544]; wfWall[592].posC = wfVerts[545];
    wfWall[593].posA = wfVerts[546]; wfWall[593].posB = wfVerts[550]; wfWall[593].posC = wfVerts[548];
    wfWall[594].posA = wfVerts[550]; wfWall[594].posB = wfVerts[546]; wfWall[594].posC = wfVerts[547];
    wfWall[595].posA = wfVerts[550]; wfWall[595].posB = wfVerts[547]; wfWall[595].posC = wfVerts[551];
    wfWall[596].posA = wfVerts[547]; wfWall[596].posB = wfVerts[546]; wfWall[596].posC = wfVerts[544];
    wfWall[597].posA = wfVerts[552]; wfWall[597].posB = wfVerts[553]; wfWall[597].posC = wfVerts[554];
    wfWall[598].posA = wfVerts[554]; wfWall[598].posB = wfVerts[553]; wfWall[598].posC = wfVerts[555];
    wfWall[599].posA = wfVerts[556]; wfWall[599].posB = wfVerts[557]; wfWall[599].posC = wfVerts[558];
    wfWall[600].posA = wfVerts[559]; wfWall[600].posB = wfVerts[560]; wfWall[600].posC = wfVerts[561];
    wfWall[601].posA = wfVerts[561]; wfWall[601].posB = wfVerts[560]; wfWall[601].posC = wfVerts[562];
    wfWall[602].posA = wfVerts[563]; wfWall[602].posB = wfVerts[564]; wfWall[602].posC = wfVerts[565];
    wfWall[603].posA = wfVerts[565]; wfWall[603].posB = wfVerts[564]; wfWall[603].posC = wfVerts[566];
    wfWall[604].posA = wfVerts[567]; wfWall[604].posB = wfVerts[557]; wfWall[604].posC = wfVerts[556];
    wfWall[605].posA = wfVerts[568]; wfWall[605].posB = wfVerts[569]; wfWall[605].posC = wfVerts[570];
    wfWall[606].posA = wfVerts[571]; wfWall[606].posB = wfVerts[572]; wfWall[606].posC = wfVerts[573];
    wfWall[607].posA = wfVerts[573]; wfWall[607].posB = wfVerts[572]; wfWall[607].posC = wfVerts[574];
    wfWall[608].posA = wfVerts[575]; wfWall[608].posB = wfVerts[570]; wfWall[608].posC = wfVerts[569];
    wfWall[609].posA = wfVerts[576]; wfWall[609].posB = wfVerts[577]; wfWall[609].posC = wfVerts[578];
    wfWall[610].posA = wfVerts[578]; wfWall[610].posB = wfVerts[577]; wfWall[610].posC = wfVerts[579];
    wfWall[611].posA = wfVerts[580]; wfWall[611].posB = wfVerts[581]; wfWall[611].posC = wfVerts[582];
    wfWall[612].posA = wfVerts[582]; wfWall[612].posB = wfVerts[581]; wfWall[612].posC = wfVerts[583];
    wfWall[613].posA = wfVerts[584]; wfWall[613].posB = wfVerts[585]; wfWall[613].posC = wfVerts[586];
    wfWall[614].posA = wfVerts[587]; wfWall[614].posB = wfVerts[586]; wfWall[614].posC = wfVerts[585];
    wfWall[615].posA = wfVerts[588]; wfWall[615].posB = wfVerts[589]; wfWall[615].posC = wfVerts[242];
    wfWall[616].posA = wfVerts[242]; wfWall[616].posB = wfVerts[589]; wfWall[616].posC = wfVerts[590];
    wfWall[617].posA = wfVerts[591]; wfWall[617].posB = wfVerts[592]; wfWall[617].posC = wfVerts[38];
    wfWall[618].posA = wfVerts[90]; wfWall[618].posB = wfVerts[593]; wfWall[618].posC = wfVerts[88];
    wfWall[619].posA = wfVerts[90]; wfWall[619].posB = wfVerts[594]; wfWall[619].posC = wfVerts[593];
    wfWall[620].posA = wfVerts[43]; wfWall[620].posB = wfVerts[595]; wfWall[620].posC = wfVerts[42];
    wfWall[621].posA = wfVerts[43]; wfWall[621].posB = wfVerts[596]; wfWall[621].posC = wfVerts[595];
    wfWall[622].posA = wfVerts[38]; wfWall[622].posB = wfVerts[596]; wfWall[622].posC = wfVerts[43];
    wfWall[623].posA = wfVerts[38]; wfWall[623].posB = wfVerts[592]; wfWall[623].posC = wfVerts[596];
    wfWall[624].posA = wfVerts[597]; wfWall[624].posB = wfVerts[598]; wfWall[624].posC = wfVerts[599];
    wfWall[625].posA = wfVerts[591]; wfWall[625].posB = wfVerts[38]; wfWall[625].posC = wfVerts[600];
    wfWall[626].posA = wfVerts[88]; wfWall[626].posB = wfVerts[591]; wfWall[626].posC = wfVerts[600];
    wfWall[627].posA = wfVerts[88]; wfWall[627].posB = wfVerts[593]; wfWall[627].posC = wfVerts[591];
    wfWall[628].posA = wfVerts[601]; wfWall[628].posB = wfVerts[594]; wfWall[628].posC = wfVerts[90];
    wfWall[629].posA = wfVerts[601]; wfWall[629].posB = wfVerts[599]; wfWall[629].posC = wfVerts[594];
    wfWall[630].posA = wfVerts[597]; wfWall[630].posB = wfVerts[599]; wfWall[630].posC = wfVerts[601];
    wfWall[631].posA = wfVerts[602]; wfWall[631].posB = wfVerts[603]; wfWall[631].posC = wfVerts[598];
    wfWall[632].posA = wfVerts[602]; wfWall[632].posB = wfVerts[598]; wfWall[632].posC = wfVerts[597];
    wfWall[633].posA = wfVerts[591]; wfWall[633].posB = wfVerts[592]; wfWall[633].posC = wfVerts[38];
    wfWall[634].posA = wfVerts[90]; wfWall[634].posB = wfVerts[593]; wfWall[634].posC = wfVerts[88];
    wfWall[635].posA = wfVerts[90]; wfWall[635].posB = wfVerts[594]; wfWall[635].posC = wfVerts[593];
    wfWall[636].posA = wfVerts[43]; wfWall[636].posB = wfVerts[595]; wfWall[636].posC = wfVerts[42];
    wfWall[637].posA = wfVerts[43]; wfWall[637].posB = wfVerts[596]; wfWall[637].posC = wfVerts[595];
    wfWall[638].posA = wfVerts[38]; wfWall[638].posB = wfVerts[596]; wfWall[638].posC = wfVerts[43];
    wfWall[639].posA = wfVerts[38]; wfWall[639].posB = wfVerts[592]; wfWall[639].posC = wfVerts[596];
    wfWall[640].posA = wfVerts[597]; wfWall[640].posB = wfVerts[598]; wfWall[640].posC = wfVerts[599];
    wfWall[641].posA = wfVerts[591]; wfWall[641].posB = wfVerts[38]; wfWall[641].posC = wfVerts[600];
    wfWall[642].posA = wfVerts[88]; wfWall[642].posB = wfVerts[591]; wfWall[642].posC = wfVerts[600];
    wfWall[643].posA = wfVerts[88]; wfWall[643].posB = wfVerts[593]; wfWall[643].posC = wfVerts[591];
    wfWall[644].posA = wfVerts[601]; wfWall[644].posB = wfVerts[594]; wfWall[644].posC = wfVerts[90];
    wfWall[645].posA = wfVerts[601]; wfWall[645].posB = wfVerts[599]; wfWall[645].posC = wfVerts[594];
    wfWall[646].posA = wfVerts[597]; wfWall[646].posB = wfVerts[599]; wfWall[646].posC = wfVerts[601];
    wfWall[647].posA = wfVerts[602]; wfWall[647].posB = wfVerts[603]; wfWall[647].posC = wfVerts[598];
    wfWall[648].posA = wfVerts[602]; wfWall[648].posB = wfVerts[598]; wfWall[648].posC = wfVerts[597];
    wfWall[649].posA = wfVerts[132]; wfWall[649].posB = wfVerts[265]; wfWall[649].posC = wfVerts[273];
    wfWall[650].posA = wfVerts[132]; wfWall[650].posB = wfVerts[273]; wfWall[650].posC = wfVerts[147];
    wfWall[651].posA = wfVerts[273]; wfWall[651].posB = wfVerts[152]; wfWall[651].posC = wfVerts[147];
    wfWall[652].posA = wfVerts[132]; wfWall[652].posB = wfVerts[604]; wfWall[652].posC = wfVerts[265];
    wfWall[653].posA = wfVerts[127]; wfWall[653].posB = wfVerts[269]; wfWall[653].posC = wfVerts[265];
    wfWall[654].posA = wfVerts[604]; wfWall[654].posB = wfVerts[134]; wfWall[654].posC = wfVerts[265];
    wfWall[655].posA = wfVerts[269]; wfWall[655].posB = wfVerts[263]; wfWall[655].posC = wfVerts[265];
    wfWall[656].posA = wfVerts[265]; wfWall[656].posB = wfVerts[134]; wfWall[656].posC = wfVerts[127];
    wfWall[657].posA = wfVerts[269]; wfWall[657].posB = wfVerts[127]; wfWall[657].posC = wfVerts[129];
    wfWall[658].posA = wfVerts[605]; wfWall[658].posB = wfVerts[606]; wfWall[658].posC = wfVerts[607];
    wfWall[659].posA = wfVerts[608]; wfWall[659].posB = wfVerts[609]; wfWall[659].posC = wfVerts[610];
    wfWall[660].posA = wfVerts[611]; wfWall[660].posB = wfVerts[608]; wfWall[660].posC = wfVerts[610];
    wfWall[661].posA = wfVerts[612]; wfWall[661].posB = wfVerts[607]; wfWall[661].posC = wfVerts[609];
    wfWall[662].posA = wfVerts[608]; wfWall[662].posB = wfVerts[612]; wfWall[662].posC = wfVerts[609];
    wfWall[663].posA = wfVerts[613]; wfWall[663].posB = wfVerts[614]; wfWall[663].posC = wfVerts[615];
    wfWall[664].posA = wfVerts[612]; wfWall[664].posB = wfVerts[605]; wfWall[664].posC = wfVerts[607];
    wfWall[665].posA = wfVerts[613]; wfWall[665].posB = wfVerts[615]; wfWall[665].posC = wfVerts[606];
    wfWall[666].posA = wfVerts[605]; wfWall[666].posB = wfVerts[613]; wfWall[666].posC = wfVerts[606];
    wfWall[667].posA = wfVerts[614]; wfWall[667].posB = wfVerts[616]; wfWall[667].posC = wfVerts[615];
    wfWall[668].posA = wfVerts[611]; wfWall[668].posB = wfVerts[610]; wfWall[668].posC = wfVerts[616];
    wfWall[669].posA = wfVerts[614]; wfWall[669].posB = wfVerts[611]; wfWall[669].posC = wfVerts[616];
    wfWall[670].posA = wfVerts[608]; wfWall[670].posB = wfVerts[605]; wfWall[670].posC = wfVerts[612];
    wfWall[671].posA = wfVerts[608]; wfWall[671].posB = wfVerts[614]; wfWall[671].posC = wfVerts[613];
    wfWall[672].posA = wfVerts[608]; wfWall[672].posB = wfVerts[613]; wfWall[672].posC = wfVerts[605];
    wfWall[673].posA = wfVerts[608]; wfWall[673].posB = wfVerts[611]; wfWall[673].posC = wfVerts[614];
    wfWall[674].posA = wfVerts[617]; wfWall[674].posB = wfVerts[618]; wfWall[674].posC = wfVerts[619];
    wfWall[675].posA = wfVerts[617]; wfWall[675].posB = wfVerts[619]; wfWall[675].posC = wfVerts[620];
    wfWall[676].posA = wfVerts[617]; wfWall[676].posB = wfVerts[620]; wfWall[676].posC = wfVerts[621];
    wfWall[677].posA = wfVerts[617]; wfWall[677].posB = wfVerts[621]; wfWall[677].posC = wfVerts[622];
    wfWall[678].posA = wfVerts[617]; wfWall[678].posB = wfVerts[622]; wfWall[678].posC = wfVerts[623];
    wfWall[679].posA = wfVerts[617]; wfWall[679].posB = wfVerts[624]; wfWall[679].posC = wfVerts[618];
    wfWall[680].posA = wfVerts[625]; wfWall[680].posB = wfVerts[626]; wfWall[680].posC = wfVerts[627];
    wfWall[681].posA = wfVerts[628]; wfWall[681].posB = wfVerts[629]; wfWall[681].posC = wfVerts[630];
    wfWall[682].posA = wfVerts[628]; wfWall[682].posB = wfVerts[630]; wfWall[682].posC = wfVerts[626];
    wfWall[683].posA = wfVerts[628]; wfWall[683].posB = wfVerts[626]; wfWall[683].posC = wfVerts[631];
    wfWall[684].posA = wfVerts[628]; wfWall[684].posB = wfVerts[631]; wfWall[684].posC = wfVerts[632];
    wfWall[685].posA = wfVerts[627]; wfWall[685].posB = wfVerts[630]; wfWall[685].posC = wfVerts[633];
    wfWall[686].posA = wfVerts[633]; wfWall[686].posB = wfVerts[629]; wfWall[686].posC = wfVerts[634];
    wfWall[687].posA = wfVerts[633]; wfWall[687].posB = wfVerts[630]; wfWall[687].posC = wfVerts[629];
    wfWall[688].posA = wfVerts[627]; wfWall[688].posB = wfVerts[626]; wfWall[688].posC = wfVerts[630];
    wfWall[689].posA = wfVerts[634]; wfWall[689].posB = wfVerts[629]; wfWall[689].posC = wfVerts[628];
    wfWall[690].posA = wfVerts[625]; wfWall[690].posB = wfVerts[631]; wfWall[690].posC = wfVerts[626];
    wfWall[691].posA = wfVerts[635]; wfWall[691].posB = wfVerts[631]; wfWall[691].posC = wfVerts[625];
    wfWall[692].posA = wfVerts[635]; wfWall[692].posB = wfVerts[632]; wfWall[692].posC = wfVerts[631];
    wfWall[693].posA = wfVerts[636]; wfWall[693].posB = wfVerts[632]; wfWall[693].posC = wfVerts[635];
    wfWall[694].posA = wfVerts[636]; wfWall[694].posB = wfVerts[628]; wfWall[694].posC = wfVerts[632];
    wfWall[695].posA = wfVerts[634]; wfWall[695].posB = wfVerts[628]; wfWall[695].posC = wfVerts[636];
    wfWall[696].posA = wfVerts[148]; wfWall[696].posB = wfVerts[637]; wfWall[696].posC = wfVerts[638];
    wfWall[697].posA = wfVerts[148]; wfWall[697].posB = wfVerts[638]; wfWall[697].posC = wfVerts[639];
    wfWall[698].posA = wfVerts[240]; wfWall[698].posB = wfVerts[640]; wfWall[698].posC = wfVerts[641];
    wfWall[699].posA = wfVerts[240]; wfWall[699].posB = wfVerts[241]; wfWall[699].posC = wfVerts[640];
    wfWall[700].posA = wfVerts[642]; wfWall[700].posB = wfVerts[5]; wfWall[700].posC = wfVerts[643];
    wfWall[701].posA = wfVerts[642]; wfWall[701].posB = wfVerts[643]; wfWall[701].posC = wfVerts[644];
    wfWall[702].posA = wfVerts[99]; wfWall[702].posB = wfVerts[645]; wfWall[702].posC = wfVerts[98];
    wfWall[703].posA = wfVerts[646]; wfWall[703].posB = wfVerts[245]; wfWall[703].posC = wfVerts[128];
    wfWall[704].posA = wfVerts[245]; wfWall[704].posB = wfVerts[647]; wfWall[704].posC = wfVerts[648];
    wfWall[705].posA = wfVerts[245]; wfWall[705].posB = wfVerts[648]; wfWall[705].posC = wfVerts[244];
    wfWall[706].posA = wfVerts[646]; wfWall[706].posB = wfVerts[647]; wfWall[706].posC = wfVerts[245];
    wfWall[707].posA = wfVerts[268]; wfWall[707].posB = wfVerts[244]; wfWall[707].posC = wfVerts[648];
    wfWall[708].posA = wfVerts[268]; wfWall[708].posB = wfVerts[648]; wfWall[708].posC = wfVerts[649];
    wfWall[709].posA = wfVerts[98]; wfWall[709].posB = wfVerts[650]; wfWall[709].posC = wfVerts[95];
    wfWall[710].posA = wfVerts[98]; wfWall[710].posB = wfVerts[645]; wfWall[710].posC = wfVerts[650];
    wfWall[711].posA = wfVerts[651]; wfWall[711].posB = wfVerts[255]; wfWall[711].posC = wfVerts[250];
    wfWall[712].posA = wfVerts[95]; wfWall[712].posB = wfVerts[650]; wfWall[712].posC = wfVerts[652];
    wfWall[713].posA = wfVerts[95]; wfWall[713].posB = wfVerts[652]; wfWall[713].posC = wfVerts[96];
    wfWall[714].posA = wfVerts[96]; wfWall[714].posB = wfVerts[652]; wfWall[714].posC = wfVerts[653];
    wfWall[715].posA = wfVerts[96]; wfWall[715].posB = wfVerts[653]; wfWall[715].posC = wfVerts[97];
    wfWall[716].posA = wfVerts[97]; wfWall[716].posB = wfVerts[653]; wfWall[716].posC = wfVerts[654];
    wfWall[717].posA = wfVerts[97]; wfWall[717].posB = wfVerts[654]; wfWall[717].posC = wfVerts[100];
    wfWall[718].posA = wfVerts[100]; wfWall[718].posB = wfVerts[654]; wfWall[718].posC = wfVerts[655];
    wfWall[719].posA = wfVerts[100]; wfWall[719].posB = wfVerts[655]; wfWall[719].posC = wfVerts[99];
    wfWall[720].posA = wfVerts[99]; wfWall[720].posB = wfVerts[655]; wfWall[720].posC = wfVerts[645];
    wfWall[721].posA = wfVerts[651]; wfWall[721].posB = wfVerts[656]; wfWall[721].posC = wfVerts[255];
    wfWall[722].posA = wfVerts[657]; wfWall[722].posB = wfVerts[658]; wfWall[722].posC = wfVerts[659];
    wfWall[723].posA = wfVerts[250]; wfWall[723].posB = wfVerts[644]; wfWall[723].posC = wfVerts[651];
    wfWall[724].posA = wfVerts[250]; wfWall[724].posB = wfVerts[642]; wfWall[724].posC = wfVerts[644];
    wfWall[725].posA = wfVerts[267]; wfWall[725].posB = wfVerts[660]; wfWall[725].posC = wfVerts[258];
    wfWall[726].posA = wfVerts[267]; wfWall[726].posB = wfVerts[258]; wfWall[726].posC = wfVerts[256];
    wfWall[727].posA = wfVerts[241]; wfWall[727].posB = wfVerts[255]; wfWall[727].posC = wfVerts[656];
    wfWall[728].posA = wfVerts[241]; wfWall[728].posB = wfVerts[656]; wfWall[728].posC = wfVerts[640];
    wfWall[729].posA = wfVerts[267]; wfWall[729].posB = wfVerts[661]; wfWall[729].posC = wfVerts[660];
    wfWall[730].posA = wfVerts[657]; wfWall[730].posB = wfVerts[161]; wfWall[730].posC = wfVerts[658];
    wfWall[731].posA = wfVerts[662]; wfWall[731].posB = wfVerts[659]; wfWall[731].posC = wfVerts[663];
    wfWall[732].posA = wfVerts[662]; wfWall[732].posB = wfVerts[657]; wfWall[732].posC = wfVerts[659];
    wfWall[733].posA = wfVerts[662]; wfWall[733].posB = wfVerts[664]; wfWall[733].posC = wfVerts[159];
    wfWall[734].posA = wfVerts[662]; wfWall[734].posB = wfVerts[663]; wfWall[734].posC = wfVerts[664];
    wfWall[735].posA = wfVerts[267]; wfWall[735].posB = wfVerts[252]; wfWall[735].posC = wfVerts[661];
    wfWall[736].posA = wfVerts[159]; wfWall[736].posB = wfVerts[665]; wfWall[736].posC = wfVerts[155];
    wfWall[737].posA = wfVerts[159]; wfWall[737].posB = wfVerts[664]; wfWall[737].posC = wfVerts[665];
    wfWall[738].posA = wfVerts[665]; wfWall[738].posB = wfVerts[148]; wfWall[738].posC = wfVerts[155];
    wfWall[739].posA = wfVerts[665]; wfWall[739].posB = wfVerts[637]; wfWall[739].posC = wfVerts[148];
    wfWall[740].posA = wfVerts[666]; wfWall[740].posB = wfVerts[141]; wfWall[740].posC = wfVerts[143];
    wfWall[741].posA = wfVerts[42]; wfWall[741].posB = wfVerts[666]; wfWall[741].posC = wfVerts[667];
    wfWall[742].posA = wfVerts[42]; wfWall[742].posB = wfVerts[668]; wfWall[742].posC = wfVerts[669];
    wfWall[743].posA = wfVerts[42]; wfWall[743].posB = wfVerts[667]; wfWall[743].posC = wfVerts[668];
    wfWall[744].posA = wfVerts[666]; wfWall[744].posB = wfVerts[41]; wfWall[744].posC = wfVerts[141];
    wfWall[745].posA = wfVerts[27]; wfWall[745].posB = wfVerts[20]; wfWall[745].posC = wfVerts[33];
    wfWall[746].posA = wfVerts[32]; wfWall[746].posB = wfVerts[31]; wfWall[746].posC = wfVerts[28];
    wfWall[747].posA = wfVerts[32]; wfWall[747].posB = wfVerts[27]; wfWall[747].posC = wfVerts[33];
    wfWall[748].posA = wfVerts[32]; wfWall[748].posB = wfVerts[28]; wfWall[748].posC = wfVerts[27];
    wfWall[749].posA = wfVerts[33]; wfWall[749].posB = wfVerts[35]; wfWall[749].posC = wfVerts[32];
    wfWall[750].posA = wfVerts[670]; wfWall[750].posB = wfVerts[671]; wfWall[750].posC = wfVerts[672];
    wfWall[751].posA = wfVerts[673]; wfWall[751].posB = wfVerts[674]; wfWall[751].posC = wfVerts[671];
    wfWall[752].posA = wfVerts[673]; wfWall[752].posB = wfVerts[671]; wfWall[752].posC = wfVerts[670];
    wfWall[753].posA = wfVerts[675]; wfWall[753].posB = wfVerts[672]; wfWall[753].posC = wfVerts[676];
    wfWall[754].posA = wfVerts[675]; wfWall[754].posB = wfVerts[676]; wfWall[754].posC = wfVerts[677];
    wfWall[755].posA = wfVerts[677]; wfWall[755].posB = wfVerts[674]; wfWall[755].posC = wfVerts[673];
    wfWall[756].posA = wfVerts[677]; wfWall[756].posB = wfVerts[676]; wfWall[756].posC = wfVerts[674];
    wfWall[757].posA = wfVerts[670]; wfWall[757].posB = wfVerts[672]; wfWall[757].posC = wfVerts[675];
    wfWall[758].posA = wfVerts[193]; wfWall[758].posB = wfVerts[190]; wfWall[758].posC = wfVerts[201];
    wfWall[759].posA = wfVerts[193]; wfWall[759].posB = wfVerts[191]; wfWall[759].posC = wfVerts[190];
    wfWall[760].posA = wfVerts[209]; wfWall[760].posB = wfVerts[206]; wfWall[760].posC = wfVerts[215];
    wfWall[761].posA = wfVerts[209]; wfWall[761].posB = wfVerts[207]; wfWall[761].posC = wfVerts[206];
    wfWall[762].posA = wfVerts[219]; wfWall[762].posB = wfVerts[221]; wfWall[762].posC = wfVerts[223];
    wfWall[763].posA = wfVerts[219]; wfWall[763].posB = wfVerts[223]; wfWall[763].posC = wfVerts[217];
    wfWall[764].posA = wfVerts[678]; wfWall[764].posB = wfVerts[679]; wfWall[764].posC = wfVerts[680];
    wfWall[765].posA = wfVerts[681]; wfWall[765].posB = wfVerts[682]; wfWall[765].posC = wfVerts[683];
    wfWall[766].posA = wfVerts[681]; wfWall[766].posB = wfVerts[683]; wfWall[766].posC = wfVerts[684];
    wfWall[767].posA = wfVerts[685]; wfWall[767].posB = wfVerts[686]; wfWall[767].posC = wfVerts[687];
    wfWall[768].posA = wfVerts[685]; wfWall[768].posB = wfVerts[687]; wfWall[768].posC = wfVerts[688];
    wfWall[769].posA = wfVerts[689]; wfWall[769].posB = wfVerts[690]; wfWall[769].posC = wfVerts[686];
    wfWall[770].posA = wfVerts[689]; wfWall[770].posB = wfVerts[686]; wfWall[770].posC = wfVerts[685];
    wfWall[771].posA = wfVerts[691]; wfWall[771].posB = wfVerts[692]; wfWall[771].posC = wfVerts[693];
    wfWall[772].posA = wfVerts[678]; wfWall[772].posB = wfVerts[694]; wfWall[772].posC = wfVerts[679];
    wfWall[773].posA = wfVerts[680]; wfWall[773].posB = wfVerts[679]; wfWall[773].posC = wfVerts[695];
    wfWall[774].posA = wfVerts[680]; wfWall[774].posB = wfVerts[695]; wfWall[774].posC = wfVerts[696];
    wfWall[775].posA = wfVerts[696]; wfWall[775].posB = wfVerts[697]; wfWall[775].posC = wfVerts[691];
    wfWall[776].posA = wfVerts[696]; wfWall[776].posB = wfVerts[695]; wfWall[776].posC = wfVerts[697];
    wfWall[777].posA = wfVerts[691]; wfWall[777].posB = wfVerts[697]; wfWall[777].posC = wfVerts[692];
    wfWall[778].posA = wfVerts[698]; wfWall[778].posB = wfVerts[694]; wfWall[778].posC = wfVerts[678];
    wfWall[779].posA = wfVerts[693]; wfWall[779].posB = wfVerts[699]; wfWall[779].posC = wfVerts[700];
    wfWall[780].posA = wfVerts[693]; wfWall[780].posB = wfVerts[692]; wfWall[780].posC = wfVerts[699];
    wfWall[781].posA = wfVerts[700]; wfWall[781].posB = wfVerts[699]; wfWall[781].posC = wfVerts[701];
    wfWall[782].posA = wfVerts[700]; wfWall[782].posB = wfVerts[701]; wfWall[782].posC = wfVerts[702];
    wfWall[783].posA = wfVerts[702]; wfWall[783].posB = wfVerts[701]; wfWall[783].posC = wfVerts[703];
    wfWall[784].posA = wfVerts[702]; wfWall[784].posB = wfVerts[703]; wfWall[784].posC = wfVerts[698];
    wfWall[785].posA = wfVerts[704]; wfWall[785].posB = wfVerts[705]; wfWall[785].posC = wfVerts[706];
    wfWall[786].posA = wfVerts[698]; wfWall[786].posB = wfVerts[703]; wfWall[786].posC = wfVerts[694];
    wfWall[787].posA = wfVerts[707]; wfWall[787].posB = wfVerts[682]; wfWall[787].posC = wfVerts[681];
    wfWall[788].posA = wfVerts[707]; wfWall[788].posB = wfVerts[708]; wfWall[788].posC = wfVerts[682];
    wfWall[789].posA = wfVerts[709]; wfWall[789].posB = wfVerts[706]; wfWall[789].posC = wfVerts[708];
    wfWall[790].posA = wfVerts[709]; wfWall[790].posB = wfVerts[708]; wfWall[790].posC = wfVerts[707];
    wfWall[791].posA = wfVerts[704]; wfWall[791].posB = wfVerts[706]; wfWall[791].posC = wfVerts[709];
    wfWall[792].posA = wfVerts[688]; wfWall[792].posB = wfVerts[687]; wfWall[792].posC = wfVerts[705];
    wfWall[793].posA = wfVerts[688]; wfWall[793].posB = wfVerts[705]; wfWall[793].posC = wfVerts[704];
    wfWall[794].posA = wfVerts[684]; wfWall[794].posB = wfVerts[683]; wfWall[794].posC = wfVerts[690];
    wfWall[795].posA = wfVerts[684]; wfWall[795].posB = wfVerts[690]; wfWall[795].posC = wfVerts[689];
    wfWall[796].posA = wfVerts[710]; wfWall[796].posB = wfVerts[711]; wfWall[796].posC = wfVerts[712];
    wfWall[797].posA = wfVerts[713]; wfWall[797].posB = wfVerts[714]; wfWall[797].posC = wfVerts[715];
    wfWall[798].posA = wfVerts[713]; wfWall[798].posB = wfVerts[716]; wfWall[798].posC = wfVerts[714];
    wfWall[799].posA = wfVerts[717]; wfWall[799].posB = wfVerts[716]; wfWall[799].posC = wfVerts[713];
    wfWall[800].posA = wfVerts[717]; wfWall[800].posB = wfVerts[718]; wfWall[800].posC = wfVerts[716];
    wfWall[801].posA = wfVerts[715]; wfWall[801].posB = wfVerts[714]; wfWall[801].posC = wfVerts[719];
    wfWall[802].posA = wfVerts[715]; wfWall[802].posB = wfVerts[719]; wfWall[802].posC = wfVerts[720];
    wfWall[803].posA = wfVerts[721]; wfWall[803].posB = wfVerts[722]; wfWall[803].posC = wfVerts[723];
    wfWall[804].posA = wfVerts[710]; wfWall[804].posB = wfVerts[712]; wfWall[804].posC = wfVerts[724];
    wfWall[805].posA = wfVerts[724]; wfWall[805].posB = wfVerts[712]; wfWall[805].posC = wfVerts[725];
    wfWall[806].posA = wfVerts[724]; wfWall[806].posB = wfVerts[725]; wfWall[806].posC = wfVerts[726];
    wfWall[807].posA = wfVerts[726]; wfWall[807].posB = wfVerts[725]; wfWall[807].posC = wfVerts[727];
    wfWall[808].posA = wfVerts[726]; wfWall[808].posB = wfVerts[727]; wfWall[808].posC = wfVerts[721];
    wfWall[809].posA = wfVerts[721]; wfWall[809].posB = wfVerts[727]; wfWall[809].posC = wfVerts[722];
    wfWall[810].posA = wfVerts[728]; wfWall[810].posB = wfVerts[729]; wfWall[810].posC = wfVerts[711];
    wfWall[811].posA = wfVerts[723]; wfWall[811].posB = wfVerts[730]; wfWall[811].posC = wfVerts[731];
    wfWall[812].posA = wfVerts[723]; wfWall[812].posB = wfVerts[722]; wfWall[812].posC = wfVerts[730];
    wfWall[813].posA = wfVerts[731]; wfWall[813].posB = wfVerts[730]; wfWall[813].posC = wfVerts[732];
    wfWall[814].posA = wfVerts[731]; wfWall[814].posB = wfVerts[732]; wfWall[814].posC = wfVerts[733];
    wfWall[815].posA = wfVerts[733]; wfWall[815].posB = wfVerts[729]; wfWall[815].posC = wfVerts[728];
    wfWall[816].posA = wfVerts[733]; wfWall[816].posB = wfVerts[732]; wfWall[816].posC = wfVerts[729];
    wfWall[817].posA = wfVerts[734]; wfWall[817].posB = wfVerts[735]; wfWall[817].posC = wfVerts[736];
    wfWall[818].posA = wfVerts[728]; wfWall[818].posB = wfVerts[711]; wfWall[818].posC = wfVerts[710];
    wfWall[819].posA = wfVerts[737]; wfWall[819].posB = wfVerts[738]; wfWall[819].posC = wfVerts[718];
    wfWall[820].posA = wfVerts[737]; wfWall[820].posB = wfVerts[718]; wfWall[820].posC = wfVerts[717];
    wfWall[821].posA = wfVerts[736]; wfWall[821].posB = wfVerts[735]; wfWall[821].posC = wfVerts[738];
    wfWall[822].posA = wfVerts[736]; wfWall[822].posB = wfVerts[738]; wfWall[822].posC = wfVerts[737];
    wfWall[823].posA = wfVerts[734]; wfWall[823].posB = wfVerts[739]; wfWall[823].posC = wfVerts[735];
    wfWall[824].posA = wfVerts[740]; wfWall[824].posB = wfVerts[741]; wfWall[824].posC = wfVerts[739];
    wfWall[825].posA = wfVerts[740]; wfWall[825].posB = wfVerts[739]; wfWall[825].posC = wfVerts[734];
    wfWall[826].posA = wfVerts[720]; wfWall[826].posB = wfVerts[741]; wfWall[826].posC = wfVerts[740];
    wfWall[827].posA = wfVerts[720]; wfWall[827].posB = wfVerts[719]; wfWall[827].posC = wfVerts[741];
    wfWall[828].posA = wfVerts[742]; wfWall[828].posB = wfVerts[743]; wfWall[828].posC = wfVerts[744];
    wfWall[829].posA = wfVerts[743]; wfWall[829].posB = wfVerts[745]; wfWall[829].posC = wfVerts[746];
    wfWall[830].posA = wfVerts[743]; wfWall[830].posB = wfVerts[746]; wfWall[830].posC = wfVerts[744];
    wfWall[831].posA = wfVerts[742]; wfWall[831].posB = wfVerts[747]; wfWall[831].posC = wfVerts[748];
    wfWall[832].posA = wfVerts[742]; wfWall[832].posB = wfVerts[749]; wfWall[832].posC = wfVerts[747];
    wfWall[833].posA = wfVerts[742]; wfWall[833].posB = wfVerts[748]; wfWall[833].posC = wfVerts[743];
    wfWall[834].posA = wfVerts[750]; wfWall[834].posB = wfVerts[751]; wfWall[834].posC = wfVerts[752];
    wfWall[835].posA = wfVerts[750]; wfWall[835].posB = wfVerts[753]; wfWall[835].posC = wfVerts[751];
    wfWall[836].posA = wfVerts[754]; wfWall[836].posB = wfVerts[753]; wfWall[836].posC = wfVerts[750];
    wfWall[837].posA = wfVerts[754]; wfWall[837].posB = wfVerts[750]; wfWall[837].posC = wfVerts[755];
    wfWall[838].posA = wfVerts[756]; wfWall[838].posB = wfVerts[751]; wfWall[838].posC = wfVerts[757];
    wfWall[839].posA = wfVerts[756]; wfWall[839].posB = wfVerts[752]; wfWall[839].posC = wfVerts[751];
    wfWall[840].posA = wfVerts[748]; wfWall[840].posB = wfVerts[747]; wfWall[840].posC = wfVerts[745];
    wfWall[841].posA = wfVerts[748]; wfWall[841].posB = wfVerts[745]; wfWall[841].posC = wfVerts[743];
    wfWall[842].posA = wfVerts[744]; wfWall[842].posB = wfVerts[749]; wfWall[842].posC = wfVerts[742];
    wfWall[843].posA = wfVerts[744]; wfWall[843].posB = wfVerts[746]; wfWall[843].posC = wfVerts[749];
    wfWall[844].posA = wfVerts[757]; wfWall[844].posB = wfVerts[751]; wfWall[844].posC = wfVerts[753];
    wfWall[845].posA = wfVerts[757]; wfWall[845].posB = wfVerts[753]; wfWall[845].posC = wfVerts[754];
    wfWall[846].posA = wfVerts[755]; wfWall[846].posB = wfVerts[752]; wfWall[846].posC = wfVerts[756];
    wfWall[847].posA = wfVerts[755]; wfWall[847].posB = wfVerts[750]; wfWall[847].posC = wfVerts[752];
    wfWall[848].posA = wfVerts[758]; wfWall[848].posB = wfVerts[759]; wfWall[848].posC = wfVerts[760];
    wfWall[849].posA = wfVerts[758]; wfWall[849].posB = wfVerts[761]; wfWall[849].posC = wfVerts[759];
    wfWall[850].posA = wfVerts[761]; wfWall[850].posB = wfVerts[762]; wfWall[850].posC = wfVerts[763];
    wfWall[851].posA = wfVerts[761]; wfWall[851].posB = wfVerts[763]; wfWall[851].posC = wfVerts[759];
    wfWall[852].posA = wfVerts[764]; wfWall[852].posB = wfVerts[765]; wfWall[852].posC = wfVerts[766];
    wfWall[853].posA = wfVerts[764]; wfWall[853].posB = wfVerts[767]; wfWall[853].posC = wfVerts[765];
    wfWall[854].posA = wfVerts[758]; wfWall[854].posB = wfVerts[762]; wfWall[854].posC = wfVerts[761];
    wfWall[855].posA = wfVerts[760]; wfWall[855].posB = wfVerts[759]; wfWall[855].posC = wfVerts[763];
    wfWall[856].posA = wfVerts[768]; wfWall[856].posB = wfVerts[769]; wfWall[856].posC = wfVerts[767];
    wfWall[857].posA = wfVerts[766]; wfWall[857].posB = wfVerts[765]; wfWall[857].posC = wfVerts[770];
    wfWall[858].posA = wfVerts[766]; wfWall[858].posB = wfVerts[770]; wfWall[858].posC = wfVerts[771];
    wfWall[859].posA = wfVerts[771]; wfWall[859].posB = wfVerts[769]; wfWall[859].posC = wfVerts[768];
    wfWall[860].posA = wfVerts[771]; wfWall[860].posB = wfVerts[770]; wfWall[860].posC = wfVerts[769];
    wfWall[861].posA = wfVerts[768]; wfWall[861].posB = wfVerts[767]; wfWall[861].posC = wfVerts[764];

    for (int i = 0; i < wfWallCount; i++) {
        wfWall[i].type = SURFACE_WALL;
        wfWall[i].center = center;
        wfWall[i].normal = norm;
        wfWall[i].center = calc_surface_center(wfWall[i]);
        wfWall[i].normal = calc_surface_norm(wfWall[i]);
    }

    wfSlope[0].posA = wfVerts[668]; wfSlope[0].posB = wfVerts[22]; wfSlope[0].posC = wfVerts[40];
    wfSlope[1].posA = wfVerts[668]; wfSlope[1].posB = wfVerts[40]; wfSlope[1].posC = wfVerts[772];
    wfSlope[2].posA = wfVerts[134]; wfSlope[2].posB = wfVerts[131]; wfSlope[2].posC = wfVerts[130];
    wfSlope[3].posA = wfVerts[134]; wfSlope[3].posB = wfVerts[604]; wfSlope[3].posC = wfVerts[131];
    wfSlope[4].posA = wfVerts[132]; wfSlope[4].posB = wfVerts[131]; wfSlope[4].posC = wfVerts[604];
    wfSlope[5].posA = wfVerts[136]; wfSlope[5].posB = wfVerts[128]; wfSlope[5].posC = wfVerts[130];
    wfSlope[6].posA = wfVerts[136]; wfSlope[6].posB = wfVerts[139]; wfSlope[6].posC = wfVerts[128];
    wfSlope[7].posA = wfVerts[260]; wfSlope[7].posB = wfVerts[266]; wfSlope[7].posC = wfVerts[159];
    wfSlope[8].posA = wfVerts[260]; wfSlope[8].posB = wfVerts[159]; wfSlope[8].posC = wfVerts[155];
    wfSlope[9].posA = wfVerts[230]; wfSlope[9].posB = wfVerts[773]; wfSlope[9].posC = wfVerts[187];
    wfSlope[10].posA = wfVerts[140]; wfSlope[10].posB = wfVerts[230]; wfSlope[10].posC = wfVerts[187];
    wfSlope[11].posA = wfVerts[269]; wfSlope[11].posB = wfVerts[128]; wfSlope[11].posC = wfVerts[245];
    wfSlope[12].posA = wfVerts[128]; wfSlope[12].posB = wfVerts[269]; wfSlope[12].posC = wfVerts[129];
    wfSlope[13].posA = wfVerts[260]; wfSlope[13].posB = wfVerts[153]; wfSlope[13].posC = wfVerts[240];
    wfSlope[14].posA = wfVerts[260]; wfSlope[14].posB = wfVerts[240]; wfSlope[14].posC = wfVerts[238];
    wfSlope[15].posA = wfVerts[257]; wfSlope[15].posB = wfVerts[642]; wfSlope[15].posC = wfVerts[5];
    wfSlope[16].posA = wfVerts[257]; wfSlope[16].posB = wfVerts[5]; wfSlope[16].posC = wfVerts[258];
    wfSlope[17].posA = wfVerts[250]; wfSlope[17].posB = wfVerts[642]; wfSlope[17].posC = wfVerts[257];
    wfSlope[18].posA = wfVerts[257]; wfSlope[18].posB = wfVerts[253]; wfSlope[18].posC = wfVerts[250];
    wfSlope[19].posA = wfVerts[269]; wfSlope[19].posB = wfVerts[245]; wfSlope[19].posC = wfVerts[268];
    wfSlope[20].posA = wfVerts[258]; wfSlope[20].posB = wfVerts[5]; wfSlope[20].posC = wfVerts[274];
    wfSlope[21].posA = wfVerts[232]; wfSlope[21].posB = wfVerts[4]; wfSlope[21].posC = wfVerts[231];
    wfSlope[22].posA = wfVerts[232]; wfSlope[22].posB = wfVerts[5]; wfSlope[22].posC = wfVerts[4];
    wfSlope[23].posA = wfVerts[5]; wfSlope[23].posB = wfVerts[232]; wfSlope[23].posC = wfVerts[230];
    wfSlope[24].posA = wfVerts[5]; wfSlope[24].posB = wfVerts[230]; wfSlope[24].posC = wfVerts[274];
    wfSlope[25].posA = wfVerts[231]; wfSlope[25].posB = wfVerts[4]; wfSlope[25].posC = wfVerts[247];
    wfSlope[26].posA = wfVerts[247]; wfSlope[26].posB = wfVerts[4]; wfSlope[26].posC = wfVerts[249];
    wfSlope[27].posA = wfVerts[245]; wfSlope[27].posB = wfVerts[244]; wfSlope[27].posC = wfVerts[268];
    wfSlope[28].posA = wfVerts[620]; wfSlope[28].posB = wfVerts[774]; wfSlope[28].posC = wfVerts[621];
    wfSlope[29].posA = wfVerts[624]; wfSlope[29].posB = wfVerts[617]; wfSlope[29].posC = wfVerts[774];
    wfSlope[30].posA = wfVerts[774]; wfSlope[30].posB = wfVerts[618]; wfSlope[30].posC = wfVerts[624];
    wfSlope[31].posA = wfVerts[774]; wfSlope[31].posB = wfVerts[619]; wfSlope[31].posC = wfVerts[618];
    wfSlope[32].posA = wfVerts[774]; wfSlope[32].posB = wfVerts[617]; wfSlope[32].posC = wfVerts[623];
    wfSlope[33].posA = wfVerts[622]; wfSlope[33].posB = wfVerts[774]; wfSlope[33].posC = wfVerts[623];
    wfSlope[34].posA = wfVerts[622]; wfSlope[34].posB = wfVerts[621]; wfSlope[34].posC = wfVerts[774];
    wfSlope[35].posA = wfVerts[620]; wfSlope[35].posB = wfVerts[619]; wfSlope[35].posC = wfVerts[774];
    wfSlope[36].posA = wfVerts[775]; wfSlope[36].posB = wfVerts[494]; wfSlope[36].posC = wfVerts[491];
    wfSlope[37].posA = wfVerts[775]; wfSlope[37].posB = wfVerts[495]; wfSlope[37].posC = wfVerts[494];
    wfSlope[38].posA = wfVerts[493]; wfSlope[38].posB = wfVerts[495]; wfSlope[38].posC = wfVerts[775];
    wfSlope[39].posA = wfVerts[493]; wfSlope[39].posB = wfVerts[492]; wfSlope[39].posC = wfVerts[495];
    wfSlope[40].posA = wfVerts[273]; wfSlope[40].posB = wfVerts[17]; wfSlope[40].posC = wfVerts[152];
    wfSlope[41].posA = wfVerts[152]; wfSlope[41].posB = wfVerts[17]; wfSlope[41].posC = wfVerts[18];
    wfSlope[42].posA = wfVerts[776]; wfSlope[42].posB = wfVerts[777]; wfSlope[42].posC = wfVerts[778];
    wfSlope[43].posA = wfVerts[135]; wfSlope[43].posB = wfVerts[668]; wfSlope[43].posC = wfVerts[779];
    wfSlope[44].posA = wfVerts[135]; wfSlope[44].posB = wfVerts[779]; wfSlope[44].posC = wfVerts[780];
    wfSlope[45].posA = wfVerts[779]; wfSlope[45].posB = wfVerts[781]; wfSlope[45].posC = wfVerts[782];
    wfSlope[46].posA = wfVerts[783]; wfSlope[46].posB = wfVerts[781]; wfSlope[46].posC = wfVerts[779];
    wfSlope[47].posA = wfVerts[668]; wfSlope[47].posB = wfVerts[783]; wfSlope[47].posC = wfVerts[779];
    wfSlope[48].posA = wfVerts[779]; wfSlope[48].posB = wfVerts[782]; wfSlope[48].posC = wfVerts[780];
    wfSlope[49].posA = wfVerts[777]; wfSlope[49].posB = wfVerts[776]; wfSlope[49].posC = wfVerts[780];
    wfSlope[50].posA = wfVerts[782]; wfSlope[50].posB = wfVerts[777]; wfSlope[50].posC = wfVerts[780];
    wfSlope[51].posA = wfVerts[668]; wfSlope[51].posB = wfVerts[784]; wfSlope[51].posC = wfVerts[785];
    wfSlope[52].posA = wfVerts[668]; wfSlope[52].posB = wfVerts[785]; wfSlope[52].posC = wfVerts[783];
    wfSlope[53].posA = wfVerts[784]; wfSlope[53].posB = wfVerts[776]; wfSlope[53].posC = wfVerts[778];
    wfSlope[54].posA = wfVerts[784]; wfSlope[54].posB = wfVerts[786]; wfSlope[54].posC = wfVerts[785];
    wfSlope[55].posA = wfVerts[784]; wfSlope[55].posB = wfVerts[778]; wfSlope[55].posC = wfVerts[786];
    wfSlope[56].posA = wfVerts[786]; wfSlope[56].posB = wfVerts[783]; wfSlope[56].posC = wfVerts[785];
    wfSlope[57].posA = wfVerts[777]; wfSlope[57].posB = wfVerts[786]; wfSlope[57].posC = wfVerts[778];
    wfSlope[58].posA = wfVerts[777]; wfSlope[58].posB = wfVerts[781]; wfSlope[58].posC = wfVerts[786];
    wfSlope[59].posA = wfVerts[786]; wfSlope[59].posB = wfVerts[781]; wfSlope[59].posC = wfVerts[783];
    wfSlope[60].posA = wfVerts[781]; wfSlope[60].posB = wfVerts[777]; wfSlope[60].posC = wfVerts[782];
    wfSlope[61].posA = wfVerts[668]; wfSlope[61].posB = wfVerts[772]; wfSlope[61].posC = wfVerts[669];

    for (int i = 0; i < wfSlopeCount; i++) {
        wfSlope[i].type = SURFACE_SLOPE;
        wfSlope[i].center = center;
        wfSlope[i].normal = norm;
        wfSlope[i].center = calc_surface_center(wfSlope[i]);
        wfSlope[i].normal = calc_surface_norm(wfSlope[i]);
    }

    wfFloor[0].posA = wfVerts[97]; wfFloor[0].posB = wfVerts[99]; wfFloor[0].posC = wfVerts[100];
    wfFloor[1].posA = wfVerts[97]; wfFloor[1].posB = wfVerts[96]; wfFloor[1].posC = wfVerts[95];
    wfFloor[2].posA = wfVerts[97]; wfFloor[2].posB = wfVerts[95]; wfFloor[2].posC = wfVerts[98];
    wfFloor[3].posA = wfVerts[97]; wfFloor[3].posB = wfVerts[98]; wfFloor[3].posC = wfVerts[99];
    wfFloor[4].posA = wfVerts[110]; wfFloor[4].posB = wfVerts[106]; wfFloor[4].posC = wfVerts[103];
    wfFloor[5].posA = wfVerts[110]; wfFloor[5].posB = wfVerts[103]; wfFloor[5].posC = wfVerts[102];
    wfFloor[6].posA = wfVerts[109]; wfFloor[6].posB = wfVerts[104]; wfFloor[6].posC = wfVerts[106];
    wfFloor[7].posA = wfVerts[109]; wfFloor[7].posB = wfVerts[108]; wfFloor[7].posC = wfVerts[107];
    wfFloor[8].posA = wfVerts[109]; wfFloor[8].posB = wfVerts[107]; wfFloor[8].posC = wfVerts[104];
    wfFloor[9].posA = wfVerts[109]; wfFloor[9].posB = wfVerts[106]; wfFloor[9].posC = wfVerts[110];
    wfFloor[10].posA = wfVerts[113]; wfFloor[10].posB = wfVerts[112]; wfFloor[10].posC = wfVerts[115];
    wfFloor[11].posA = wfVerts[113]; wfFloor[11].posB = wfVerts[115]; wfFloor[11].posC = wfVerts[117];
    wfFloor[12].posA = wfVerts[121]; wfFloor[12].posB = wfVerts[120]; wfFloor[12].posC = wfVerts[124];
    wfFloor[13].posA = wfVerts[121]; wfFloor[13].posB = wfVerts[124]; wfFloor[13].posC = wfVerts[122];
    wfFloor[14].posA = wfVerts[133]; wfFloor[14].posB = wfVerts[146]; wfFloor[14].posC = wfVerts[131];
    wfFloor[15].posA = wfVerts[136]; wfFloor[15].posB = wfVerts[130]; wfFloor[15].posC = wfVerts[131];
    wfFloor[16].posA = wfVerts[136]; wfFloor[16].posB = wfVerts[131]; wfFloor[16].posC = wfVerts[137];
    wfFloor[17].posA = wfVerts[148]; wfFloor[17].posB = wfVerts[496]; wfFloor[17].posC = wfVerts[498];
    wfFloor[18].posA = wfVerts[639]; wfFloor[18].posB = wfVerts[496]; wfFloor[18].posC = wfVerts[148];
    wfFloor[19].posA = wfVerts[148]; wfFloor[19].posB = wfVerts[502]; wfFloor[19].posC = wfVerts[155];
    wfFloor[20].posA = wfVerts[148]; wfFloor[20].posB = wfVerts[498]; wfFloor[20].posC = wfVerts[502];
    wfFloor[21].posA = wfVerts[496]; wfFloor[21].posB = wfVerts[639]; wfFloor[21].posC = wfVerts[153];
    wfFloor[22].posA = wfVerts[496]; wfFloor[22].posB = wfVerts[153]; wfFloor[22].posC = wfVerts[500];
    wfFloor[23].posA = wfVerts[145]; wfFloor[23].posB = wfVerts[128]; wfFloor[23].posC = wfVerts[139];
    wfFloor[24].posA = wfVerts[145]; wfFloor[24].posB = wfVerts[164]; wfFloor[24].posC = wfVerts[128];
    wfFloor[25].posA = wfVerts[151]; wfFloor[25].posB = wfVerts[639]; wfFloor[25].posC = wfVerts[146];
    wfFloor[26].posA = wfVerts[151]; wfFloor[26].posB = wfVerts[146]; wfFloor[26].posC = wfVerts[133];
    wfFloor[27].posA = wfVerts[502]; wfFloor[27].posB = wfVerts[153]; wfFloor[27].posC = wfVerts[260];
    wfFloor[28].posA = wfVerts[502]; wfFloor[28].posB = wfVerts[500]; wfFloor[28].posC = wfVerts[153];
    wfFloor[29].posA = wfVerts[502]; wfFloor[29].posB = wfVerts[260]; wfFloor[29].posC = wfVerts[155];
    wfFloor[30].posA = wfVerts[156]; wfFloor[30].posB = wfVerts[158]; wfFloor[30].posC = wfVerts[266];
    wfFloor[31].posA = wfVerts[156]; wfFloor[31].posB = wfVerts[266]; wfFloor[31].posC = wfVerts[161];
    wfFloor[32].posA = wfVerts[170]; wfFloor[32].posB = wfVerts[174]; wfFloor[32].posC = wfVerts[176];
    wfFloor[33].posA = wfVerts[182]; wfFloor[33].posB = wfVerts[183]; wfFloor[33].posC = wfVerts[180];
    wfFloor[34].posA = wfVerts[183]; wfFloor[34].posB = wfVerts[186]; wfFloor[34].posC = wfVerts[180];
    wfFloor[35].posA = wfVerts[145]; wfFloor[35].posB = wfVerts[169]; wfFloor[35].posC = wfVerts[164];
    wfFloor[36].posA = wfVerts[145]; wfFloor[36].posB = wfVerts[167]; wfFloor[36].posC = wfVerts[169];
    wfFloor[37].posA = wfVerts[170]; wfFloor[37].posB = wfVerts[176]; wfFloor[37].posC = wfVerts[168];
    wfFloor[38].posA = wfVerts[177]; wfFloor[38].posB = wfVerts[178]; wfFloor[38].posC = wfVerts[175];
    wfFloor[39].posA = wfVerts[177]; wfFloor[39].posB = wfVerts[171]; wfFloor[39].posC = wfVerts[178];
    wfFloor[40].posA = wfVerts[172]; wfFloor[40].posB = wfVerts[181]; wfFloor[40].posC = wfVerts[173];
    wfFloor[41].posA = wfVerts[172]; wfFloor[41].posB = wfVerts[179]; wfFloor[41].posC = wfVerts[181];
    wfFloor[42].posA = wfVerts[184]; wfFloor[42].posB = wfVerts[187]; wfFloor[42].posC = wfVerts[773];
    wfFloor[43].posA = wfVerts[184]; wfFloor[43].posB = wfVerts[773]; wfFloor[43].posC = wfVerts[185];
    wfFloor[44].posA = wfVerts[198]; wfFloor[44].posB = wfVerts[188]; wfFloor[44].posC = wfVerts[196];
    wfFloor[45].posA = wfVerts[198]; wfFloor[45].posB = wfVerts[189]; wfFloor[45].posC = wfVerts[188];
    wfFloor[46].posA = wfVerts[202]; wfFloor[46].posB = wfVerts[205]; wfFloor[46].posC = wfVerts[203];
    wfFloor[47].posA = wfVerts[227]; wfFloor[47].posB = wfVerts[222]; wfFloor[47].posC = wfVerts[225];
    wfFloor[48].posA = wfVerts[227]; wfFloor[48].posB = wfVerts[224]; wfFloor[48].posC = wfVerts[222];
    wfFloor[49].posA = wfVerts[410]; wfFloor[49].posB = wfVerts[406]; wfFloor[49].posC = wfVerts[408];
    wfFloor[50].posA = wfVerts[410]; wfFloor[50].posB = wfVerts[403]; wfFloor[50].posC = wfVerts[406];
    wfFloor[51].posA = wfVerts[418]; wfFloor[51].posB = wfVerts[414]; wfFloor[51].posC = wfVerts[416];
    wfFloor[52].posA = wfVerts[418]; wfFloor[52].posB = wfVerts[411]; wfFloor[52].posC = wfVerts[414];
    wfFloor[53].posA = wfVerts[426]; wfFloor[53].posB = wfVerts[422]; wfFloor[53].posC = wfVerts[424];
    wfFloor[54].posA = wfVerts[426]; wfFloor[54].posB = wfVerts[419]; wfFloor[54].posC = wfVerts[422];
    wfFloor[55].posA = wfVerts[434]; wfFloor[55].posB = wfVerts[430]; wfFloor[55].posC = wfVerts[432];
    wfFloor[56].posA = wfVerts[434]; wfFloor[56].posB = wfVerts[427]; wfFloor[56].posC = wfVerts[430];
    wfFloor[57].posA = wfVerts[442]; wfFloor[57].posB = wfVerts[438]; wfFloor[57].posC = wfVerts[440];
    wfFloor[58].posA = wfVerts[442]; wfFloor[58].posB = wfVerts[435]; wfFloor[58].posC = wfVerts[438];
    wfFloor[59].posA = wfVerts[450]; wfFloor[59].posB = wfVerts[446]; wfFloor[59].posC = wfVerts[448];
    wfFloor[60].posA = wfVerts[450]; wfFloor[60].posB = wfVerts[443]; wfFloor[60].posC = wfVerts[446];
    wfFloor[61].posA = wfVerts[458]; wfFloor[61].posB = wfVerts[454]; wfFloor[61].posC = wfVerts[456];
    wfFloor[62].posA = wfVerts[458]; wfFloor[62].posB = wfVerts[451]; wfFloor[62].posC = wfVerts[454];
    wfFloor[63].posA = wfVerts[466]; wfFloor[63].posB = wfVerts[462]; wfFloor[63].posC = wfVerts[464];
    wfFloor[64].posA = wfVerts[466]; wfFloor[64].posB = wfVerts[459]; wfFloor[64].posC = wfVerts[462];
    wfFloor[65].posA = wfVerts[164]; wfFloor[65].posB = wfVerts[231]; wfFloor[65].posC = wfVerts[247];
    wfFloor[66].posA = wfVerts[164]; wfFloor[66].posB = wfVerts[247]; wfFloor[66].posC = wfVerts[245];
    wfFloor[67].posA = wfVerts[4]; wfFloor[67].posB = wfVerts[9]; wfFloor[67].posC = wfVerts[268];
    wfFloor[68].posA = wfVerts[4]; wfFloor[68].posB = wfVerts[10]; wfFloor[68].posC = wfVerts[9];
    wfFloor[69].posA = wfVerts[240]; wfFloor[69].posB = wfVerts[13]; wfFloor[69].posC = wfVerts[241];
    wfFloor[70].posA = wfVerts[13]; wfFloor[70].posB = wfVerts[240]; wfFloor[70].posC = wfVerts[234];
    wfFloor[71].posA = wfVerts[13]; wfFloor[71].posB = wfVerts[234]; wfFloor[71].posC = wfVerts[233];
    wfFloor[72].posA = wfVerts[241]; wfFloor[72].posB = wfVerts[13]; wfFloor[72].posC = wfVerts[255];
    wfFloor[73].posA = wfVerts[262]; wfFloor[73].posB = wfVerts[9]; wfFloor[73].posC = wfVerts[16];
    wfFloor[74].posA = wfVerts[9]; wfFloor[74].posB = wfVerts[262]; wfFloor[74].posC = wfVerts[264];
    wfFloor[75].posA = wfVerts[256]; wfFloor[75].posB = wfVerts[274]; wfFloor[75].posC = wfVerts[230];
    wfFloor[76].posA = wfVerts[2]; wfFloor[76].posB = wfVerts[642]; wfFloor[76].posC = wfVerts[0];
    wfFloor[77].posA = wfVerts[2]; wfFloor[77].posB = wfVerts[5]; wfFloor[77].posC = wfVerts[642];
    wfFloor[78].posA = wfVerts[250]; wfFloor[78].posB = wfVerts[7]; wfFloor[78].posC = wfVerts[0];
    wfFloor[79].posA = wfVerts[250]; wfFloor[79].posB = wfVerts[255]; wfFloor[79].posC = wfVerts[7];
    wfFloor[80].posA = wfVerts[164]; wfFloor[80].posB = wfVerts[245]; wfFloor[80].posC = wfVerts[128];
    wfFloor[81].posA = wfVerts[267]; wfFloor[81].posB = wfVerts[256]; wfFloor[81].posC = wfVerts[230];
    wfFloor[82].posA = wfVerts[267]; wfFloor[82].posB = wfVerts[230]; wfFloor[82].posC = wfVerts[252];
    wfFloor[83].posA = wfVerts[255]; wfFloor[83].posB = wfVerts[13]; wfFloor[83].posC = wfVerts[7];
    wfFloor[84].posA = wfVerts[250]; wfFloor[84].posB = wfVerts[0]; wfFloor[84].posC = wfVerts[642];
    wfFloor[85].posA = wfVerts[15]; wfFloor[85].posB = wfVerts[262]; wfFloor[85].posC = wfVerts[16];
    wfFloor[86].posA = wfVerts[271]; wfFloor[86].posB = wfVerts[15]; wfFloor[86].posC = wfVerts[272];
    wfFloor[87].posA = wfVerts[271]; wfFloor[87].posB = wfVerts[262]; wfFloor[87].posC = wfVerts[15];
    wfFloor[88].posA = wfVerts[330]; wfFloor[88].posB = wfVerts[237]; wfFloor[88].posC = wfVerts[277];
    wfFloor[89].posA = wfVerts[282]; wfFloor[89].posB = wfVerts[284]; wfFloor[89].posC = wfVerts[280];
    wfFloor[90].posA = wfVerts[282]; wfFloor[90].posB = wfVerts[280]; wfFloor[90].posC = wfVerts[279];
    wfFloor[91].posA = wfVerts[237]; wfFloor[91].posB = wfVerts[239]; wfFloor[91].posC = wfVerts[290];
    wfFloor[92].posA = wfVerts[237]; wfFloor[92].posB = wfVerts[290]; wfFloor[92].posC = wfVerts[277];
    wfFloor[93].posA = wfVerts[239]; wfFloor[93].posB = wfVerts[332]; wfFloor[93].posC = wfVerts[290];
    wfFloor[94].posA = wfVerts[332]; wfFloor[94].posB = wfVerts[289]; wfFloor[94].posC = wfVerts[290];
    wfFloor[95].posA = wfVerts[330]; wfFloor[95].posB = wfVerts[277]; wfFloor[95].posC = wfVerts[287];
    wfFloor[96].posA = wfVerts[332]; wfFloor[96].posB = wfVerts[330]; wfFloor[96].posC = wfVerts[287];
    wfFloor[97].posA = wfVerts[332]; wfFloor[97].posB = wfVerts[287]; wfFloor[97].posC = wfVerts[289];
    wfFloor[98].posA = wfVerts[241]; wfFloor[98].posB = wfVerts[327]; wfFloor[98].posC = wfVerts[328];
    wfFloor[99].posA = wfVerts[328]; wfFloor[99].posB = wfVerts[327]; wfFloor[99].posC = wfVerts[326];
    wfFloor[100].posA = wfVerts[233]; wfFloor[100].posB = wfVerts[234]; wfFloor[100].posC = wfVerts[334];
    wfFloor[101].posA = wfVerts[339]; wfFloor[101].posB = wfVerts[335]; wfFloor[101].posC = wfVerts[337];
    wfFloor[102].posA = wfVerts[339]; wfFloor[102].posB = wfVerts[341]; wfFloor[102].posC = wfVerts[335];
    wfFloor[103].posA = wfVerts[345]; wfFloor[103].posB = wfVerts[350]; wfFloor[103].posC = wfVerts[347];
    wfFloor[104].posA = wfVerts[345]; wfFloor[104].posB = wfVerts[347]; wfFloor[104].posC = wfVerts[343];
    wfFloor[105].posA = wfVerts[353]; wfFloor[105].posB = wfVerts[358]; wfFloor[105].posC = wfVerts[355];
    wfFloor[106].posA = wfVerts[353]; wfFloor[106].posB = wfVerts[355]; wfFloor[106].posC = wfVerts[351];
    wfFloor[107].posA = wfVerts[359]; wfFloor[107].posB = wfVerts[787]; wfFloor[107].posC = wfVerts[788];
    wfFloor[108].posA = wfVerts[359]; wfFloor[108].posB = wfVerts[362]; wfFloor[108].posC = wfVerts[787];
    wfFloor[109].posA = wfVerts[363]; wfFloor[109].posB = wfVerts[789]; wfFloor[109].posC = wfVerts[790];
    wfFloor[110].posA = wfVerts[363]; wfFloor[110].posB = wfVerts[366]; wfFloor[110].posC = wfVerts[789];
    wfFloor[111].posA = wfVerts[353]; wfFloor[111].posB = wfVerts[140]; wfFloor[111].posC = wfVerts[358];
    wfFloor[112].posA = wfVerts[353]; wfFloor[112].posB = wfVerts[252]; wfFloor[112].posC = wfVerts[140];
    wfFloor[113].posA = wfVerts[373]; wfFloor[113].posB = wfVerts[376]; wfFloor[113].posC = wfVerts[374];
    wfFloor[114].posA = wfVerts[373]; wfFloor[114].posB = wfVerts[374]; wfFloor[114].posC = wfVerts[372];
    wfFloor[115].posA = wfVerts[378]; wfFloor[115].posB = wfVerts[271]; wfFloor[115].posC = wfVerts[272];
    wfFloor[116].posA = wfVerts[474]; wfFloor[116].posB = wfVerts[489]; wfFloor[116].posC = wfVerts[479];
    wfFloor[117].posA = wfVerts[477]; wfFloor[117].posB = wfVerts[470]; wfFloor[117].posC = wfVerts[475];
    wfFloor[118].posA = wfVerts[477]; wfFloor[118].posB = wfVerts[469]; wfFloor[118].posC = wfVerts[470];
    wfFloor[119].posA = wfVerts[468]; wfFloor[119].posB = wfVerts[477]; wfFloor[119].posC = wfVerts[487];
    wfFloor[120].posA = wfVerts[468]; wfFloor[120].posB = wfVerts[469]; wfFloor[120].posC = wfVerts[477];
    wfFloor[121].posA = wfVerts[472]; wfFloor[121].posB = wfVerts[487]; wfFloor[121].posC = wfVerts[489];
    wfFloor[122].posA = wfVerts[472]; wfFloor[122].posB = wfVerts[468]; wfFloor[122].posC = wfVerts[487];
    wfFloor[123].posA = wfVerts[471]; wfFloor[123].posB = wfVerts[467]; wfFloor[123].posC = wfVerts[484];
    wfFloor[124].posA = wfVerts[474]; wfFloor[124].posB = wfVerts[472]; wfFloor[124].posC = wfVerts[489];
    wfFloor[125].posA = wfVerts[473]; wfFloor[125].posB = wfVerts[479]; wfFloor[125].posC = wfVerts[481];
    wfFloor[126].posA = wfVerts[473]; wfFloor[126].posB = wfVerts[474]; wfFloor[126].posC = wfVerts[479];
    wfFloor[127].posA = wfVerts[467]; wfFloor[127].posB = wfVerts[473]; wfFloor[127].posC = wfVerts[481];
    wfFloor[128].posA = wfVerts[467]; wfFloor[128].posB = wfVerts[481]; wfFloor[128].posC = wfVerts[484];
    wfFloor[129].posA = wfVerts[471]; wfFloor[129].posB = wfVerts[484]; wfFloor[129].posC = wfVerts[482];
    wfFloor[130].posA = wfVerts[470]; wfFloor[130].posB = wfVerts[482]; wfFloor[130].posC = wfVerts[475];
    wfFloor[131].posA = wfVerts[470]; wfFloor[131].posB = wfVerts[471]; wfFloor[131].posC = wfVerts[482];
    wfFloor[132].posA = wfVerts[1]; wfFloor[132].posB = wfVerts[3]; wfFloor[132].posC = wfVerts[14];
    wfFloor[133].posA = wfVerts[6]; wfFloor[133].posB = wfVerts[1]; wfFloor[133].posC = wfVerts[11];
    wfFloor[134].posA = wfVerts[11]; wfFloor[134].posB = wfVerts[1]; wfFloor[134].posC = wfVerts[14];
    wfFloor[135].posA = wfVerts[3]; wfFloor[135].posB = wfVerts[8]; wfFloor[135].posC = wfVerts[14];
    wfFloor[136].posA = wfVerts[14]; wfFloor[136].posB = wfVerts[12]; wfFloor[136].posC = wfVerts[11];
    wfFloor[137].posA = wfVerts[497]; wfFloor[137].posB = wfVerts[501]; wfFloor[137].posC = wfVerts[503];
    wfFloor[138].posA = wfVerts[497]; wfFloor[138].posB = wfVerts[499]; wfFloor[138].posC = wfVerts[501];
    wfFloor[139].posA = wfVerts[510]; wfFloor[139].posB = wfVerts[511]; wfFloor[139].posC = wfVerts[508];
    wfFloor[140].posA = wfVerts[510]; wfFloor[140].posB = wfVerts[508]; wfFloor[140].posC = wfVerts[507];
    wfFloor[141].posA = wfVerts[518]; wfFloor[141].posB = wfVerts[519]; wfFloor[141].posC = wfVerts[516];
    wfFloor[142].posA = wfVerts[518]; wfFloor[142].posB = wfVerts[516]; wfFloor[142].posC = wfVerts[515];
    wfFloor[143].posA = wfVerts[523]; wfFloor[143].posB = wfVerts[518]; wfFloor[143].posC = wfVerts[515];
    wfFloor[144].posA = wfVerts[523]; wfFloor[144].posB = wfVerts[515]; wfFloor[144].posC = wfVerts[521];
    wfFloor[145].posA = wfVerts[527]; wfFloor[145].posB = wfVerts[523]; wfFloor[145].posC = wfVerts[521];
    wfFloor[146].posA = wfVerts[527]; wfFloor[146].posB = wfVerts[521]; wfFloor[146].posC = wfVerts[525];
    wfFloor[147].posA = wfVerts[531]; wfFloor[147].posB = wfVerts[527]; wfFloor[147].posC = wfVerts[525];
    wfFloor[148].posA = wfVerts[531]; wfFloor[148].posB = wfVerts[525]; wfFloor[148].posC = wfVerts[529];
    wfFloor[149].posA = wfVerts[538]; wfFloor[149].posB = wfVerts[539]; wfFloor[149].posC = wfVerts[536];
    wfFloor[150].posA = wfVerts[538]; wfFloor[150].posB = wfVerts[536]; wfFloor[150].posC = wfVerts[535];
    wfFloor[151].posA = wfVerts[543]; wfFloor[151].posB = wfVerts[538]; wfFloor[151].posC = wfVerts[535];
    wfFloor[152].posA = wfVerts[543]; wfFloor[152].posB = wfVerts[535]; wfFloor[152].posC = wfVerts[541];
    wfFloor[153].posA = wfVerts[547]; wfFloor[153].posB = wfVerts[543]; wfFloor[153].posC = wfVerts[541];
    wfFloor[154].posA = wfVerts[547]; wfFloor[154].posB = wfVerts[541]; wfFloor[154].posC = wfVerts[545];
    wfFloor[155].posA = wfVerts[551]; wfFloor[155].posB = wfVerts[547]; wfFloor[155].posC = wfVerts[545];
    wfFloor[156].posA = wfVerts[551]; wfFloor[156].posB = wfVerts[545]; wfFloor[156].posC = wfVerts[549];
    wfFloor[157].posA = wfVerts[564]; wfFloor[157].posB = wfVerts[562]; wfFloor[157].posC = wfVerts[566];
    wfFloor[158].posA = wfVerts[553]; wfFloor[158].posB = wfVerts[559]; wfFloor[158].posC = wfVerts[555];
    wfFloor[159].posA = wfVerts[555]; wfFloor[159].posB = wfVerts[559]; wfFloor[159].posC = wfVerts[561];
    wfFloor[160].posA = wfVerts[791]; wfFloor[160].posB = wfVerts[588]; wfFloor[160].posC = wfVerts[245];
    wfFloor[161].posA = wfVerts[242]; wfFloor[161].posB = wfVerts[245]; wfFloor[161].posC = wfVerts[588];
    wfFloor[162].posA = wfVerts[566]; wfFloor[162].posB = wfVerts[562]; wfFloor[162].posC = wfVerts[560];
    wfFloor[163].posA = wfVerts[565]; wfFloor[163].posB = wfVerts[558]; wfFloor[163].posC = wfVerts[563];
    wfFloor[164].posA = wfVerts[563]; wfFloor[164].posB = wfVerts[558]; wfFloor[164].posC = wfVerts[557];
    wfFloor[165].posA = wfVerts[556]; wfFloor[165].posB = wfVerts[574]; wfFloor[165].posC = wfVerts[567];
    wfFloor[166].posA = wfVerts[567]; wfFloor[166].posB = wfVerts[574]; wfFloor[166].posC = wfVerts[572];
    wfFloor[167].posA = wfVerts[568]; wfFloor[167].posB = wfVerts[579]; wfFloor[167].posC = wfVerts[577];
    wfFloor[168].posA = wfVerts[573]; wfFloor[168].posB = wfVerts[575]; wfFloor[168].posC = wfVerts[571];
    wfFloor[169].posA = wfVerts[571]; wfFloor[169].posB = wfVerts[575]; wfFloor[169].posC = wfVerts[569];
    wfFloor[170].posA = wfVerts[570]; wfFloor[170].posB = wfVerts[579]; wfFloor[170].posC = wfVerts[568];
    wfFloor[171].posA = wfVerts[582]; wfFloor[171].posB = wfVerts[587]; wfFloor[171].posC = wfVerts[580];
    wfFloor[172].posA = wfVerts[578]; wfFloor[172].posB = wfVerts[583]; wfFloor[172].posC = wfVerts[576];
    wfFloor[173].posA = wfVerts[581]; wfFloor[173].posB = wfVerts[576]; wfFloor[173].posC = wfVerts[583];
    wfFloor[174].posA = wfVerts[584]; wfFloor[174].posB = wfVerts[590]; wfFloor[174].posC = wfVerts[589];
    wfFloor[175].posA = wfVerts[580]; wfFloor[175].posB = wfVerts[587]; wfFloor[175].posC = wfVerts[585];
    wfFloor[176].posA = wfVerts[586]; wfFloor[176].posB = wfVerts[590]; wfFloor[176].posC = wfVerts[584];
    wfFloor[177].posA = wfVerts[485]; wfFloor[177].posB = wfVerts[480]; wfFloor[177].posC = wfVerts[488];
    wfFloor[178].posA = wfVerts[485]; wfFloor[178].posB = wfVerts[488]; wfFloor[178].posC = wfVerts[490];
    wfFloor[179].posA = wfVerts[485]; wfFloor[179].posB = wfVerts[490]; wfFloor[179].posC = wfVerts[486];
    wfFloor[180].posA = wfVerts[485]; wfFloor[180].posB = wfVerts[486]; wfFloor[180].posC = wfVerts[476];
    wfFloor[181].posA = wfVerts[485]; wfFloor[181].posB = wfVerts[476]; wfFloor[181].posC = wfVerts[478];
    wfFloor[182].posA = wfVerts[485]; wfFloor[182].posB = wfVerts[478]; wfFloor[182].posC = wfVerts[483];
    wfFloor[183].posA = wfVerts[667]; wfFloor[183].posB = wfVerts[666]; wfFloor[183].posC = wfVerts[143];
    wfFloor[184].posA = wfVerts[667]; wfFloor[184].posB = wfVerts[143]; wfFloor[184].posC = wfVerts[138];
    wfFloor[185].posA = wfVerts[679]; wfFloor[185].posB = wfVerts[703]; wfFloor[185].posC = wfVerts[701];
    wfFloor[186].posA = wfVerts[679]; wfFloor[186].posB = wfVerts[697]; wfFloor[186].posC = wfVerts[695];
    wfFloor[187].posA = wfVerts[679]; wfFloor[187].posB = wfVerts[694]; wfFloor[187].posC = wfVerts[703];
    wfFloor[188].posA = wfVerts[679]; wfFloor[188].posB = wfVerts[701]; wfFloor[188].posC = wfVerts[699];
    wfFloor[189].posA = wfVerts[679]; wfFloor[189].posB = wfVerts[699]; wfFloor[189].posC = wfVerts[692];
    wfFloor[190].posA = wfVerts[679]; wfFloor[190].posB = wfVerts[692]; wfFloor[190].posC = wfVerts[697];
    wfFloor[191].posA = wfVerts[683]; wfFloor[191].posB = wfVerts[686]; wfFloor[191].posC = wfVerts[690];
    wfFloor[192].posA = wfVerts[683]; wfFloor[192].posB = wfVerts[687]; wfFloor[192].posC = wfVerts[686];
    wfFloor[193].posA = wfVerts[683]; wfFloor[193].posB = wfVerts[682]; wfFloor[193].posC = wfVerts[708];
    wfFloor[194].posA = wfVerts[683]; wfFloor[194].posB = wfVerts[708]; wfFloor[194].posC = wfVerts[706];
    wfFloor[195].posA = wfVerts[683]; wfFloor[195].posB = wfVerts[705]; wfFloor[195].posC = wfVerts[687];
    wfFloor[196].posA = wfVerts[683]; wfFloor[196].posB = wfVerts[706]; wfFloor[196].posC = wfVerts[705];
    wfFloor[197].posA = wfVerts[712]; wfFloor[197].posB = wfVerts[732]; wfFloor[197].posC = wfVerts[730];
    wfFloor[198].posA = wfVerts[712]; wfFloor[198].posB = wfVerts[722]; wfFloor[198].posC = wfVerts[727];
    wfFloor[199].posA = wfVerts[712]; wfFloor[199].posB = wfVerts[727]; wfFloor[199].posC = wfVerts[725];
    wfFloor[200].posA = wfVerts[712]; wfFloor[200].posB = wfVerts[730]; wfFloor[200].posC = wfVerts[722];
    wfFloor[201].posA = wfVerts[712]; wfFloor[201].posB = wfVerts[729]; wfFloor[201].posC = wfVerts[732];
    wfFloor[202].posA = wfVerts[712]; wfFloor[202].posB = wfVerts[711]; wfFloor[202].posC = wfVerts[729];
    wfFloor[203].posA = wfVerts[735]; wfFloor[203].posB = wfVerts[741]; wfFloor[203].posC = wfVerts[719];
    wfFloor[204].posA = wfVerts[735]; wfFloor[204].posB = wfVerts[739]; wfFloor[204].posC = wfVerts[741];
    wfFloor[205].posA = wfVerts[735]; wfFloor[205].posB = wfVerts[718]; wfFloor[205].posC = wfVerts[738];
    wfFloor[206].posA = wfVerts[735]; wfFloor[206].posB = wfVerts[716]; wfFloor[206].posC = wfVerts[718];
    wfFloor[207].posA = wfVerts[735]; wfFloor[207].posB = wfVerts[719]; wfFloor[207].posC = wfVerts[714];
    wfFloor[208].posA = wfVerts[735]; wfFloor[208].posB = wfVerts[714]; wfFloor[208].posC = wfVerts[716];
    wfFloor[209].posA = wfVerts[792]; wfFloor[209].posB = wfVerts[793]; wfFloor[209].posC = wfVerts[794];
    wfFloor[210].posA = wfVerts[795]; wfFloor[210].posB = wfVerts[796]; wfFloor[210].posC = wfVerts[797];
    wfFloor[211].posA = wfVerts[746]; wfFloor[211].posB = wfVerts[747]; wfFloor[211].posC = wfVerts[749];
    wfFloor[212].posA = wfVerts[746]; wfFloor[212].posB = wfVerts[745]; wfFloor[212].posC = wfVerts[747];
    wfFloor[213].posA = wfVerts[756]; wfFloor[213].posB = wfVerts[754]; wfFloor[213].posC = wfVerts[755];
    wfFloor[214].posA = wfVerts[756]; wfFloor[214].posB = wfVerts[757]; wfFloor[214].posC = wfVerts[754];
    wfFloor[215].posA = wfVerts[668]; wfFloor[215].posB = wfVerts[144]; wfFloor[215].posC = wfVerts[23];
    wfFloor[216].posA = wfVerts[668]; wfFloor[216].posB = wfVerts[23]; wfFloor[216].posC = wfVerts[22];
    wfFloor[217].posA = wfVerts[19]; wfFloor[217].posB = wfVerts[36]; wfFloor[217].posC = wfVerts[34];
    wfFloor[218].posA = wfVerts[19]; wfFloor[218].posB = wfVerts[30]; wfFloor[218].posC = wfVerts[36];
    wfFloor[219].posA = wfVerts[19]; wfFloor[219].posB = wfVerts[21]; wfFloor[219].posC = wfVerts[26];
    wfFloor[220].posA = wfVerts[19]; wfFloor[220].posB = wfVerts[26]; wfFloor[220].posC = wfVerts[29];
    wfFloor[221].posA = wfVerts[44]; wfFloor[221].posB = wfVerts[38]; wfFloor[221].posC = wfVerts[772];
    wfFloor[222].posA = wfVerts[43]; wfFloor[222].posB = wfVerts[669]; wfFloor[222].posC = wfVerts[38];
    wfFloor[223].posA = wfVerts[43]; wfFloor[223].posB = wfVerts[42]; wfFloor[223].posC = wfVerts[669];
    wfFloor[224].posA = wfVerts[669]; wfFloor[224].posB = wfVerts[772]; wfFloor[224].posC = wfVerts[38];
    wfFloor[225].posA = wfVerts[44]; wfFloor[225].posB = wfVerts[772]; wfFloor[225].posC = wfVerts[40];
    wfFloor[226].posA = wfVerts[44]; wfFloor[226].posB = wfVerts[94]; wfFloor[226].posC = wfVerts[90];
    wfFloor[227].posA = wfVerts[44]; wfFloor[227].posB = wfVerts[86]; wfFloor[227].posC = wfVerts[94];
    wfFloor[228].posA = wfVerts[44]; wfFloor[228].posB = wfVerts[90]; wfFloor[228].posC = wfVerts[88];
    wfFloor[229].posA = wfVerts[44]; wfFloor[229].posB = wfVerts[92]; wfFloor[229].posC = wfVerts[86];
    wfFloor[230].posA = wfVerts[50]; wfFloor[230].posB = wfVerts[55]; wfFloor[230].posC = wfVerts[47];
    wfFloor[231].posA = wfVerts[50]; wfFloor[231].posB = wfVerts[47]; wfFloor[231].posC = wfVerts[46];
    wfFloor[232].posA = wfVerts[50]; wfFloor[232].posB = wfVerts[52]; wfFloor[232].posC = wfVerts[51];
    wfFloor[233].posA = wfVerts[50]; wfFloor[233].posB = wfVerts[46]; wfFloor[233].posC = wfVerts[52];
    wfFloor[234].posA = wfVerts[50]; wfFloor[234].posB = wfVerts[51]; wfFloor[234].posC = wfVerts[49];
    wfFloor[235].posA = wfVerts[50]; wfFloor[235].posB = wfVerts[53]; wfFloor[235].posC = wfVerts[57];
    wfFloor[236].posA = wfVerts[50]; wfFloor[236].posB = wfVerts[58]; wfFloor[236].posC = wfVerts[54];
    wfFloor[237].posA = wfVerts[50]; wfFloor[237].posB = wfVerts[54]; wfFloor[237].posC = wfVerts[53];
    wfFloor[238].posA = wfVerts[50]; wfFloor[238].posB = wfVerts[57]; wfFloor[238].posC = wfVerts[56];
    wfFloor[239].posA = wfVerts[50]; wfFloor[239].posB = wfVerts[56]; wfFloor[239].posC = wfVerts[55];
    wfFloor[240].posA = wfVerts[63]; wfFloor[240].posB = wfVerts[68]; wfFloor[240].posC = wfVerts[60];
    wfFloor[241].posA = wfVerts[63]; wfFloor[241].posB = wfVerts[60]; wfFloor[241].posC = wfVerts[59];
    wfFloor[242].posA = wfVerts[63]; wfFloor[242].posB = wfVerts[65]; wfFloor[242].posC = wfVerts[64];
    wfFloor[243].posA = wfVerts[63]; wfFloor[243].posB = wfVerts[59]; wfFloor[243].posC = wfVerts[65];
    wfFloor[244].posA = wfVerts[63]; wfFloor[244].posB = wfVerts[64]; wfFloor[244].posC = wfVerts[62];
    wfFloor[245].posA = wfVerts[63]; wfFloor[245].posB = wfVerts[66]; wfFloor[245].posC = wfVerts[70];
    wfFloor[246].posA = wfVerts[63]; wfFloor[246].posB = wfVerts[71]; wfFloor[246].posC = wfVerts[67];
    wfFloor[247].posA = wfVerts[63]; wfFloor[247].posB = wfVerts[67]; wfFloor[247].posC = wfVerts[66];
    wfFloor[248].posA = wfVerts[63]; wfFloor[248].posB = wfVerts[70]; wfFloor[248].posC = wfVerts[69];
    wfFloor[249].posA = wfVerts[63]; wfFloor[249].posB = wfVerts[69]; wfFloor[249].posC = wfVerts[68];
    wfFloor[250].posA = wfVerts[76]; wfFloor[250].posB = wfVerts[81]; wfFloor[250].posC = wfVerts[73];
    wfFloor[251].posA = wfVerts[76]; wfFloor[251].posB = wfVerts[73]; wfFloor[251].posC = wfVerts[72];
    wfFloor[252].posA = wfVerts[76]; wfFloor[252].posB = wfVerts[78]; wfFloor[252].posC = wfVerts[77];
    wfFloor[253].posA = wfVerts[76]; wfFloor[253].posB = wfVerts[72]; wfFloor[253].posC = wfVerts[78];
    wfFloor[254].posA = wfVerts[76]; wfFloor[254].posB = wfVerts[77]; wfFloor[254].posC = wfVerts[75];
    wfFloor[255].posA = wfVerts[76]; wfFloor[255].posB = wfVerts[79]; wfFloor[255].posC = wfVerts[83];
    wfFloor[256].posA = wfVerts[76]; wfFloor[256].posB = wfVerts[84]; wfFloor[256].posC = wfVerts[80];
    wfFloor[257].posA = wfVerts[76]; wfFloor[257].posB = wfVerts[80]; wfFloor[257].posC = wfVerts[79];
    wfFloor[258].posA = wfVerts[76]; wfFloor[258].posB = wfVerts[83]; wfFloor[258].posC = wfVerts[82];
    wfFloor[259].posA = wfVerts[76]; wfFloor[259].posB = wfVerts[82]; wfFloor[259].posC = wfVerts[81];
    wfFloor[260].posA = wfVerts[798]; wfFloor[260].posB = wfVerts[799]; wfFloor[260].posC = wfVerts[800];
    wfFloor[261].posA = wfVerts[798]; wfFloor[261].posB = wfVerts[800]; wfFloor[261].posC = wfVerts[801];
    wfFloor[262].posA = wfVerts[767]; wfFloor[262].posB = wfVerts[769]; wfFloor[262].posC = wfVerts[770];
    wfFloor[263].posA = wfVerts[767]; wfFloor[263].posB = wfVerts[770]; wfFloor[263].posC = wfVerts[765];

    for (int i = 0; i < wfFloorCount; i++) {
        wfFloor[i].type = SURFACE_FLOOR;
        wfFloor[i].center = center;
        wfFloor[i].normal = norm;
        wfFloor[i].center = calc_surface_center(wfFloor[i]);
    }

    // Allocate map's matrix and construct
    wfMatFP = malloc_uncached(sizeof(T3DMat4FP));
    t3d_mat4fp_from_srt_euler(wfMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    // Load model
    modelWF = t3d_model_load("rom:/wf.t3dm");

    // Create map's RSPQ block
    rspq_block_begin();
        t3d_matrix_push(wfMatFP);
        matCount++;
        rdpq_set_prim_color(WHITE);
        t3d_model_draw(modelWF);
        t3d_matrix_pop(1);
    dplWF = rspq_block_end();

}