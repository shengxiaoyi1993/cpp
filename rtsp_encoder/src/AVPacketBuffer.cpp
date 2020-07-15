#include "AVPacketBuffer.h"
#include <iostream>
#include <vector>
#include <mutex>
#include "unistd.h"
#include <thread>
#include <pthread.h>

using namespace std;
//#define DEBUG_AVPACKETBUFFER


AVPacketBuffer::AVPacketBuffer(uint v_size):
    _header(nullptr),
    _pointer(nullptr),
    _isValid(false),
    _size(v_size)
{
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif
    pthread_mutex_init(&_mutex,nullptr);
    AVPacketNode* psupnode =nullptr;
    for(uint i=0;i<v_size;i++){
        AVPacketNode* tmpnode=AVPacketNode::getAVPacketNode();
        if(tmpnode == nullptr){
            _isValid=false;
            cout<<__func__<<":fail to malloc"<<endl;
            exit(1);
        }
        if(_header == nullptr){
            _header=tmpnode;
            _pointer=_header;
            psupnode=tmpnode;
        }
        else{
            tmpnode->_front=psupnode;
            psupnode->_next=tmpnode;
            psupnode=tmpnode;
        }
    }
    _header->_front=psupnode;
    psupnode->_next=_header;
    _isValid=true;

}


AVPacketBuffer::~AVPacketBuffer(){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif

    _isValid=false;
    setThreadLock();
    AVPacketNode* psupnode =_header->_next;
    do{
        av_free_packet(&psupnode->_packet);
        free(psupnode);
        psupnode=psupnode->_next;

    }while(psupnode!=_header);

    av_free_packet(&psupnode->_packet);
    free(psupnode);
    setTreadUnlock();

    psupnode=nullptr;
}



bool AVPacketBuffer::setPacketNode(const AVPacket v_pkt){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
        cout<<__func__<<"ThreadID:"<<this_thread::get_id()<<endl;
#endif

    if(_isValid){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<" out mutex"<<endl;
#endif
        setThreadLock();
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<" in mutex"<<endl;
#endif
        _pointer=_pointer->_next;
        av_free_packet(&_pointer->_packet);
        av_copy_packet(&_pointer->_packet,&v_pkt);
        setTreadUnlock();
        if(!_isReady){
            static uint count=0;
            count++;
            if(count==_size){
                _isReady=true;
            }
        }

#ifdef DEBUG_AVPACKETBUFFER
        cout<<"v_pkt.flags:"<<v_pkt.flags<<endl;
        cout<<"_pointer->_packet.flags:"<<_pointer->_packet.flags<<endl;
        //    cout<<"reset pkt:"<<_pointer->_seq<<endl;
#endif
        return true;
    }
    else{
        return false;
    }
}

//寻找与指定帧之前最近的关键帧
//v_seq 为负值，-v_seq即为距离当前点的距离
//v_offset为正值，为检测出来的关键帧距离当前点的距离
AVPacketNode* AVPacketBuffer::findKeyFrame(int v_seq,int & v_offset){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif

    AVPacketNode* ret=nullptr;
    AVPacketNode* psupnode =_pointer;
    v_offset=0;

    if(_isValid&&(-v_seq<static_cast<int>(_size))){
        if(v_seq>0){
        }
        else{
            for(int i=0;i<-v_seq;i++){
                psupnode=psupnode->_front;
                v_offset++;
            }
            while(psupnode!= _pointer->_next &&
                  (psupnode->_packet.flags != AV_PKT_FLAG_KEY)){
                v_offset++;
                psupnode=psupnode->_front;
            }
            if(psupnode->_packet.flags == AV_PKT_FLAG_KEY){
                ret = psupnode;
            }
        }
    }

    return ret;

}



bool AVPacketBuffer::getPacketNode(int v_seq, AVPacket& v_pkt){
#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif

    if(_isValid&&(abs(v_seq)<static_cast<int>(_size))){
        AVPacketNode* psupnode =_pointer;
        if(v_seq>0){
            return false;
        }
        else{
            for(int i=0;i<-v_seq;i++){
                psupnode=psupnode->_front;
            }
        }
        av_copy_packet(&v_pkt,&psupnode->_packet);
        return true;
    }
    else{
        return false;
    }

}


void AVPacketBuffer::printPktBuf(){

#ifdef DEBUG_AVPACKETBUFFER
        cout<<__func__<<endl;
#endif
        AVPacketNode* psupnode =_header;
    do{
        if(psupnode == nullptr){
            cout<<"psupnode ias null"<<endl;
            break;
        }
//        cout<<"flags:"<<psupnode->_packet.flags<<endl;
        psupnode=psupnode->_next;

    }while(psupnode!=_header);
    fflush(stdout);
    return;

}






