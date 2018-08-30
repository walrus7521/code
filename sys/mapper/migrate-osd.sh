#!/bin/bash
FIRSTIDX=0
ENDIDX=1
NODE=9
CLUSTERNAME=cephprod01
JDEV=/dev/sdd

ceph --cluster $CLUSTERNAME osd set noout

parted -s $JDEV mklabel gpt
parted -s $JDEV mkpart journal 2 5122
parted -s $JDEV mkpart journal 5123 10243                                       

for ((osd=$FIRSTIDX;osd<=$ENDIDX;osd++)); do
   echo "OSD $osd"
   /etc/init.d/ceph --cluster $CLUSTERNAME stop osd.$osd
   ceph-osd --cluster=$CLUSTERNAME --flush-journal -i $osd 
   rm /var/lib/ceph/osd/$CLUSTERNAME-$osd/journal

   partnum=$[$osd - $FIRSTIDX]
   partnum=$[$partnum + 1]
   echo "OSD: $osd  partnum: $partnum"

   ln -s $JDEV$partnum /var/lib/ceph/osd/$CLUSTERNAME-$osd/journal
   ceph-osd --cluster=$CLUSTERNAME --mkjournal -i $osd
   ceph -c /etc/ceph/$CLUSTERNAME.conf --name=osd.$osd --keyring=/var/lib/ceph/osd/$CLUSTERNAME-$osd/keyring osd crush create-or-move -- $osd 1 host=r305-1u$NODE-ceph-a root=default
   /etc/init.d/ceph --cluster $CLUSTERNAME start osd.$osd
done



exit

