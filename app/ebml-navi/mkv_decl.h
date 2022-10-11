#ifndef EBML_NAVI_MKV_DECL_H
#define EBML_NAVI_MKV_DECL_H

#include "oddebml/oEbmlDecl.h"

#define EBML_MKV_DECL_LIST_ \
   XMAP_C_( Segment, 0x18538067,1,0, o_EbmlMaster ) \
   XMAP_C_( SeekHead, 0x114d9b74,0,1, o_EbmlMaster ) \
   XMAP_C_( Seek, 0x4dbb,1,1, o_EbmlMaster ) \
   XMAP_C_( SeekID, 0x53ab,1,0, o_EbmlBinary ) \
   XMAP_C_( SeekPosition, 0x53ac,1,0, o_EbmlUint ) \
   XMAP_C_( Info, 0x1549a966,1,0, o_EbmlMaster ) \
   XMAP_C_( SegmentUID, 0x73a4,0,0, o_EbmlBinary ) \
   XMAP_C_( SegmentFilename, 0x7384,0,0, o_EbmlUtf8 ) \
   XMAP_C_( PrevUID, 0x3cb923,0,0, o_EbmlBinary ) \
   XMAP_C_( PrevFilename, 0x3c83ab,0,0, o_EbmlUtf8 ) \
   XMAP_C_( NextUID, 0x3eb923,0,0, o_EbmlBinary ) \
   XMAP_C_( NextFilename, 0x3e83bb,0,0, o_EbmlUtf8 ) \
   XMAP_C_( SegmentFamily, 0x4444,0,1, o_EbmlBinary ) \
   XMAP_C_( ChapterTranslate, 0x6924,0,1, o_EbmlMaster ) \
   XMAP_C_( ChapterTranslateEditionUID, 0x69fc,0,1, o_EbmlUint ) \
   XMAP_C_( ChapterTranslateCodec, 0x69bf,1,0, o_EbmlUint ) \
   XMAP_C_( ChapterTranslateID, 0x69a5,1,0, o_EbmlBinary ) \
   XMAP_C_( TimestampScale, 0x2ad7b1,1,0, o_EbmlUint ) \
   XMAP_C_( Duration, 0x4489,0,0, o_EbmlFloat ) \
   XMAP_C_( DateUTC, 0x4461,0,0, o_EbmlDate ) \
   XMAP_C_( Title, 0x7ba9,0,0, o_EbmlUtf8 ) \
   XMAP_C_( MuxingApp, 0x4d80,1,0, o_EbmlUtf8 ) \
   XMAP_C_( WritingApp, 0x5741,1,0, o_EbmlUtf8 ) \
   XMAP_C_( Cluster, 0x1f43b675,0,1, o_EbmlMaster ) \
   XMAP_C_( Timestamp, 0xe7,1,0, o_EbmlUint ) \
   XMAP_C_( SilentTracks, 0x5854,0,0, o_EbmlMaster ) \
   XMAP_C_( SilentTrackNumber, 0x58d7,0,1, o_EbmlUint ) \
   XMAP_C_( Position, 0xa7,0,0, o_EbmlUint ) \
   XMAP_C_( PrevSize, 0xab,0,0, o_EbmlUint ) \
   XMAP_C_( SimpleBlock, 0xa3,0,1, o_EbmlBinary ) \
   XMAP_C_( BlockGroup, 0xa0,0,1, o_EbmlMaster ) \
   XMAP_C_( Block, 0xa1,1,0, o_EbmlBinary ) \
   XMAP_C_( BlockVirtual, 0xa2,0,0, o_EbmlBinary ) \
   XMAP_C_( BlockAdditions, 0x75a1,0,0, o_EbmlMaster ) \
   XMAP_C_( BlockMore, 0xa6,1,1, o_EbmlMaster ) \
   XMAP_C_( BlockAddID, 0xee,1,0, o_EbmlUint ) \
   XMAP_C_( BlockAdditional, 0xa5,1,0, o_EbmlBinary ) \
   XMAP_C_( BlockDuration, 0x9b,0,0, o_EbmlUint ) \
   XMAP_C_( ReferencePriority, 0xfa,1,0, o_EbmlUint ) \
   XMAP_C_( ReferenceBlock, 0xfb,0,1, o_EbmlInt ) \
   XMAP_C_( ReferenceVirtual, 0xfd,0,0, o_EbmlInt ) \
   XMAP_C_( CodecState, 0xa4,0,0, o_EbmlBinary ) \
   XMAP_C_( DiscardPadding, 0x75a2,0,0, o_EbmlBinary ) \
   XMAP_C_( Slices, 0x8e,0,0, o_EbmlMaster ) \
   XMAP_C_( TimeSlice, 0xe8,0,1, o_EbmlMaster ) \
   XMAP_C_( LaceNumber, 0xcc,0,0, o_EbmlUint ) \
   XMAP_C_( FrameNumber, 0xcd,0,0, o_EbmlUint ) \
   XMAP_C_( BlockAdditionID, 0xcb,0,0, o_EbmlUint ) \
   XMAP_C_( Delay, 0xce,0,0, o_EbmlUint ) \
   XMAP_C_( SliceDuration, 0xcf,0,0, o_EbmlUint ) \
   XMAP_C_( ReferenceFrame, 0xc8,0,0, o_EbmlMaster ) \
   XMAP_C_( ReferenceOffset, 0xc9,1,0, o_EbmlUint ) \
   XMAP_C_( ReferenceTimestamp, 0xca,1,0, o_EbmlUint ) \
   XMAP_C_( EncryptedBlock, 0xaf,0,1, o_EbmlBinary ) \
   XMAP_C_( Tracks, 0x1654ae6b,0,0, o_EbmlMaster ) \
   XMAP_C_( TrackEntry, 0xae,1,1, o_EbmlMaster ) \
   XMAP_C_( TrackNumber, 0xd7,1,0, o_EbmlUint ) \
   XMAP_C_( TrackUID, 0x73c5,1,0, o_EbmlUint ) \
   XMAP_C_( TrackType, 0x83,1,0, o_EbmlUint ) \
   XMAP_C_( FlagEnabled, 0xb9,1,0, o_EbmlUint ) \
   XMAP_C_( FlagDefault, 0x88,1,0, o_EbmlUint ) \
   XMAP_C_( FlagForced, 0x55aa,1,0, o_EbmlUint ) \
   XMAP_C_( FlagHearingImpaired, 0x55ab,0,0, o_EbmlUint ) \
   XMAP_C_( FlagVisualImpaired, 0x55ac,0,0, o_EbmlUint ) \
   XMAP_C_( FlagTextDescriptions, 0x55ad,0,0, o_EbmlUint ) \
   XMAP_C_( FlagOriginal, 0x55ae,0,0, o_EbmlUint ) \
   XMAP_C_( FlagCommentary, 0x55af,0,0, o_EbmlUint ) \
   XMAP_C_( FlagLacing, 0x9c,1,0, o_EbmlUint ) \
   XMAP_C_( MinCache, 0x6de7,1,0, o_EbmlUint ) \
   XMAP_C_( MaxCache, 0x6df8,0,0, o_EbmlUint ) \
   XMAP_C_( DefaultDuration, 0x23e383,0,0, o_EbmlUint ) \
   XMAP_C_( DefaultDecodedFieldDuration, 0x234e7a,0,0, o_EbmlUint ) \
   XMAP_C_( TrackTimestampScale, 0x23314f,1,0, o_EbmlFloat ) \
   XMAP_C_( TrackOffset, 0x537f,0,0, o_EbmlInt ) \
   XMAP_C_( MaxBlockAdditionID, 0x55ee,1,0, o_EbmlUint ) \
   XMAP_C_( BlockAdditionMapping, 0x41e4,0,1, o_EbmlMaster ) \
   XMAP_C_( BlockAddIDValue, 0x41f0,0,0, o_EbmlUint ) \
   XMAP_C_( BlockAddIDName, 0x41a4,0,0, o_EbmlString ) \
   XMAP_C_( BlockAddIDType, 0x41e7,1,0, o_EbmlUint ) \
   XMAP_C_( BlockAddIDExtraData, 0x41ed,0,0, o_EbmlBinary ) \
   XMAP_C_( Name, 0x536e,0,0, o_EbmlUtf8 ) \
   XMAP_C_( Language, 0x22b59c,0,0, o_EbmlString ) \
   XMAP_C_( LanguageIETF, 0x22b59d,0,0, o_EbmlString ) \
   XMAP_C_( CodecID, 0x86,1,0, o_EbmlString ) \
   XMAP_C_( CodecPrivate, 0x63a2,0,0, o_EbmlBinary ) \
   XMAP_C_( CodecName, 0x258688,0,0, o_EbmlUtf8 ) \
   XMAP_C_( AttachmentLink, 0x7446,0,0, o_EbmlUint ) \
   XMAP_C_( CodecSettings, 0x3a9697,0,0, o_EbmlUtf8 ) \
   XMAP_C_( CodecInfoURL, 0x3b4040,0,1, o_EbmlString ) \
   XMAP_C_( CodecDownloadURL, 0x26b240,0,1, o_EbmlString ) \
   XMAP_C_( CodecDecodeAll, 0xaa,1,0, o_EbmlUint ) \
   XMAP_C_( TrackOverlay, 0x6fab,0,1, o_EbmlUint ) \
   XMAP_C_( CodecDelay, 0x56aa,0,0, o_EbmlUint ) \
   XMAP_C_( SeekPreRoll, 0x56bb,1,0, o_EbmlUint ) \
   XMAP_C_( TrackTranslate, 0x6624,0,1, o_EbmlMaster ) \
   XMAP_C_( TrackTranslateEditionUID, 0x66fc,0,1, o_EbmlUint ) \
   XMAP_C_( TrackTranslateCodec, 0x66bf,1,0, o_EbmlUint ) \
   XMAP_C_( TrackTranslateTrackID, 0x66a5,1,0, o_EbmlBinary ) \
   XMAP_C_( Video, 0xe0,0,0, o_EbmlMaster ) \
   XMAP_C_( FlagInterlaced, 0x9a,1,0, o_EbmlUint ) \
   XMAP_C_( FieldOrder, 0x9d,1,0, o_EbmlUint ) \
   XMAP_C_( StereoMode, 0x53b8,0,0, o_EbmlUint ) \
   XMAP_C_( AlphaMode, 0x53c0,0,0, o_EbmlUint ) \
   XMAP_C_( OldStereoMode, 0x53b9,0,0, o_EbmlUint ) \
   XMAP_C_( PixelWidth, 0xb0,1,0, o_EbmlUint ) \
   XMAP_C_( PixelHeight, 0xba,1,0, o_EbmlUint ) \
   XMAP_C_( PixelCropBottom, 0x54aa,0,0, o_EbmlUint ) \
   XMAP_C_( PixelCropTop, 0x54bb,0,0, o_EbmlUint ) \
   XMAP_C_( PixelCropLeft, 0x54cc,0,0, o_EbmlUint ) \
   XMAP_C_( PixelCropRight, 0x54dd,0,0, o_EbmlUint ) \
   XMAP_C_( DisplayWidth, 0x54b0,0,0, o_EbmlUint ) \
   XMAP_C_( DisplayHeight, 0x54ba,0,0, o_EbmlUint ) \
   XMAP_C_( DisplayUnit, 0x54b2,0,0, o_EbmlUint ) \
   XMAP_C_( AspectRatioType, 0x54b3,0,0, o_EbmlUint ) \
   XMAP_C_( ColourSpace, 0x2eb524,0,0, o_EbmlBinary ) \
   XMAP_C_( GammaValue, 0x2fb523,0,0, o_EbmlFloat ) \
   XMAP_C_( FrameRate, 0x2383e3,0,0, o_EbmlFloat ) \
   XMAP_C_( Colour, 0x55b0,0,0, o_EbmlMaster ) \
   XMAP_C_( MatrixCoefficients, 0x55b1,0,0, o_EbmlUint ) \
   XMAP_C_( BitsPerChannel, 0x55b2,0,0, o_EbmlUint ) \
   XMAP_C_( ChromaSubsamplingHorz, 0x55b3,0,0, o_EbmlUint ) \
   XMAP_C_( ChromaSubsamplingVert, 0x55b4,0,0, o_EbmlUint ) \
   XMAP_C_( CbSubsamplingHorz, 0x55b5,0,0, o_EbmlUint ) \
   XMAP_C_( CbSubsamplingVert, 0x55b6,0,0, o_EbmlUint ) \
   XMAP_C_( ChromaSitingHorz, 0x55b7,0,0, o_EbmlUint ) \
   XMAP_C_( ChromaSitingVert, 0x55b8,0,0, o_EbmlUint ) \
   XMAP_C_( Range, 0x55b9,0,0, o_EbmlUint ) \
   XMAP_C_( TransferCharacteristics, 0x55ba,0,0, o_EbmlUint ) \
   XMAP_C_( Primaries, 0x55bb,0,0, o_EbmlUint ) \
   XMAP_C_( MaxCLL, 0x55bc,0,0, o_EbmlUint ) \
   XMAP_C_( MaxFALL, 0x55bd,0,0, o_EbmlUint ) \
   XMAP_C_( MasteringMetadata, 0x55d0,0,0, o_EbmlMaster ) \
   XMAP_C_( PrimaryRChromaticityX, 0x55d1,0,0, o_EbmlFloat ) \
   XMAP_C_( PrimaryRChromaticityY, 0x55d2,0,0, o_EbmlFloat ) \
   XMAP_C_( PrimaryGChromaticityX, 0x55d3,0,0, o_EbmlFloat ) \
   XMAP_C_( PrimaryGChromaticityY, 0x55d4,0,0, o_EbmlFloat ) \
   XMAP_C_( PrimaryBChromaticityX, 0x55d5,0,0, o_EbmlFloat ) \
   XMAP_C_( PrimaryBChromaticityY, 0x55d6,0,0, o_EbmlFloat ) \
   XMAP_C_( WhitePointChromaticityX, 0x55d7,0,0, o_EbmlFloat ) \
   XMAP_C_( WhitePointChromaticityY, 0x55d8,0,0, o_EbmlFloat ) \
   XMAP_C_( LuminanceMax, 0x55d9,0,0, o_EbmlFloat ) \
   XMAP_C_( LuminanceMin, 0x55da,0,0, o_EbmlFloat ) \
   XMAP_C_( Projection, 0x7670,0,0, o_EbmlMaster ) \
   XMAP_C_( ProjectionType, 0x7671,1,0, o_EbmlUint ) \
   XMAP_C_( ProjectionPrivate, 0x7672,0,0, o_EbmlBinary ) \
   XMAP_C_( ProjectionPoseYaw, 0x7673,1,0, o_EbmlFloat ) \
   XMAP_C_( ProjectionPosePitch, 0x7674,1,0, o_EbmlFloat ) \
   XMAP_C_( ProjectionPoseRoll, 0x7675,1,0, o_EbmlFloat ) \
   XMAP_C_( Audio, 0xe1,0,0, o_EbmlMaster ) \
   XMAP_C_( SamplingFrequency, 0xb5,1,0, o_EbmlFloat ) \
   XMAP_C_( OutputSamplingFrequency, 0x78b5,0,0, o_EbmlFloat ) \
   XMAP_C_( Channels, 0x9f,1,0, o_EbmlUint ) \
   XMAP_C_( ChannelPositions, 0x7d7b,0,0, o_EbmlBinary ) \
   XMAP_C_( BitDepth, 0x6264,0,0, o_EbmlUint ) \
   XMAP_C_( TrackOperation, 0xe2,0,0, o_EbmlMaster ) \
   XMAP_C_( TrackCombinePlanes, 0xe3,0,0, o_EbmlMaster ) \
   XMAP_C_( TrackPlane, 0xe4,1,1, o_EbmlMaster ) \
   XMAP_C_( TrackPlaneUID, 0xe5,1,0, o_EbmlUint ) \
   XMAP_C_( TrackPlaneType, 0xe6,1,0, o_EbmlUint ) \
   XMAP_C_( TrackJoinBlocks, 0xe9,0,0, o_EbmlMaster ) \
   XMAP_C_( TrackJoinUID, 0xed,1,1, o_EbmlUint ) \
   XMAP_C_( TrickTrackUID, 0xc0,0,0, o_EbmlUint ) \
   XMAP_C_( TrickTrackSegmentUID, 0xc1,0,0, o_EbmlBinary ) \
   XMAP_C_( TrickTrackFlag, 0xc6,0,0, o_EbmlUint ) \
   XMAP_C_( TrickMasterTrackUID, 0xc7,0,0, o_EbmlUint ) \
   XMAP_C_( TrickMasterTrackSegmentUID, 0xc4,0,0, o_EbmlBinary ) \
   XMAP_C_( ContentEncodings, 0x6d80,0,0, o_EbmlMaster ) \
   XMAP_C_( ContentEncoding, 0x6240,1,1, o_EbmlMaster ) \
   XMAP_C_( ContentEncodingOrder, 0x5031,1,0, o_EbmlUint ) \
   XMAP_C_( ContentEncodingScope, 0x5032,1,0, o_EbmlUint ) \
   XMAP_C_( ContentEncodingType, 0x5033,1,0, o_EbmlUint ) \
   XMAP_C_( ContentCompression, 0x5034,0,0, o_EbmlMaster ) \
   XMAP_C_( ContentCompAlgo, 0x4254,1,0, o_EbmlUint ) \
   XMAP_C_( ContentCompSettings, 0x4255,0,0, o_EbmlBinary ) \
   XMAP_C_( ContentEncryption, 0x5035,0,0, o_EbmlMaster ) \
   XMAP_C_( ContentEncAlgo, 0x47e1,1,0, o_EbmlUint ) \
   XMAP_C_( ContentEncKeyID, 0x47e2,0,0, o_EbmlBinary ) \
   XMAP_C_( ContentEncAESSettings, 0x47e7,0,0, o_EbmlMaster ) \
   XMAP_C_( AESSettingsCipherMode, 0x47e8,1,0, o_EbmlUint ) \
   XMAP_C_( ContentSignature, 0x47e3,0,0, o_EbmlBinary ) \
   XMAP_C_( ContentSigKeyID, 0x47e4,0,0, o_EbmlBinary ) \
   XMAP_C_( ContentSigAlgo, 0x47e5,0,0, o_EbmlUint ) \
   XMAP_C_( ContentSigHashAlgo, 0x47e6,0,0, o_EbmlUint ) \
   XMAP_C_( Cues, 0x1c53bb6b,0,0, o_EbmlMaster ) \
   XMAP_C_( CuePoint, 0xbb,1,1, o_EbmlMaster ) \
   XMAP_C_( CueTime, 0xb3,1,0, o_EbmlUint ) \
   XMAP_C_( CueTrackPositions, 0xb7,1,1, o_EbmlMaster ) \
   XMAP_C_( CueTrack, 0xf7,1,0, o_EbmlUint ) \
   XMAP_C_( CueClusterPosition, 0xf1,1,0, o_EbmlUint ) \
   XMAP_C_( CueRelativePosition, 0xf0,0,0, o_EbmlUint ) \
   XMAP_C_( CueDuration, 0xb2,0,0, o_EbmlUint ) \
   XMAP_C_( CueBlockNumber, 0x5378,0,0, o_EbmlUint ) \
   XMAP_C_( CueCodecState, 0xea,0,0, o_EbmlUint ) \
   XMAP_C_( CueReference, 0xdb,0,1, o_EbmlMaster ) \
   XMAP_C_( CueRefTime, 0x96,1,0, o_EbmlUint ) \
   XMAP_C_( CueRefCluster, 0x97,1,0, o_EbmlUint ) \
   XMAP_C_( CueRefNumber, 0x535f,0,0, o_EbmlUint ) \
   XMAP_C_( CueRefCodecState, 0xeb,0,0, o_EbmlUint ) \
   XMAP_C_( Attachments, 0x1941a469,0,0, o_EbmlMaster ) \
   XMAP_C_( AttachedFile, 0x61a7,1,1, o_EbmlMaster ) \
   XMAP_C_( FileDescription, 0x467e,0,0, o_EbmlUtf8 ) \
   XMAP_C_( FileName, 0x466e,1,0, o_EbmlUtf8 ) \
   XMAP_C_( FileMimeType, 0x4660,1,0, o_EbmlString ) \
   XMAP_C_( FileData, 0x465c,1,0, o_EbmlBinary ) \
   XMAP_C_( FileUID, 0x46ae,1,0, o_EbmlUint ) \
   XMAP_C_( FileReferral, 0x4675,0,0, o_EbmlBinary ) \
   XMAP_C_( FileUsedStartTime, 0x4661,0,0, o_EbmlUint ) \
   XMAP_C_( FileUsedEndTime, 0x4662,0,0, o_EbmlUint ) \
   XMAP_C_( Chapters, 0x1043a770,0,0, o_EbmlMaster ) \
   XMAP_C_( EditionEntry, 0x45b9,1,1, o_EbmlMaster ) \
   XMAP_C_( EditionUID, 0x45BC,0,0, o_EbmlUint ) \
   XMAP_C_( EditionFlagHidden, 0x45bd,1,0, o_EbmlUint ) \
   XMAP_C_( EditionFlagDefault, 0x45db,1,0, o_EbmlUint ) \
   XMAP_C_( EditionFlagOrdered, 0x45dd,0,0, o_EbmlUint ) \
   XMAP_C_( ChapterAtom, 0xb6,1,1, o_EbmlMaster ) \
   XMAP_C_( ChapterUID, 0x73C4,1,0, o_EbmlUint ) \
   XMAP_C_( ChapterStringUID, 0x5654,0,0, o_EbmlUtf8 ) \
   XMAP_C_( ChapterTimeStart, 0x91,1,0, o_EbmlUint ) \
   XMAP_C_( ChapterTimeEnd, 0x92,0,0, o_EbmlUint ) \
   XMAP_C_( ChapterFlagHidden, 0x98,1,0, o_EbmlUint ) \
   XMAP_C_( ChapterFlagEnabled, 0x4598,1,0, o_EbmlUint ) \
   XMAP_C_( ChapterSegmentUID, 0x6e67,0,0, o_EbmlBinary ) \
   XMAP_C_( ChapterSegmentEditionUID, 0x6ebc,0,0, o_EbmlUint ) \
   XMAP_C_( ChapterPhysicalEquiv, 0x63c3,0,0, o_EbmlUint ) \
   XMAP_C_( ChapterTrack, 0x8f,0,0, o_EbmlMaster ) \
   XMAP_C_( ChapterTrackUID, 0x89,1,1, o_EbmlUint ) \
   XMAP_C_( ChapterDisplay, 0x80,0,1, o_EbmlMaster ) \
   XMAP_C_( ChapString, 0x85,1,0, o_EbmlUtf8 ) \
   XMAP_C_( ChapLanguage, 0x437c,1,1, o_EbmlString ) \
   XMAP_C_( ChapLanguageIETF, 0x437d,0,1, o_EbmlString ) \
   XMAP_C_( ChapCountry, 0x437e,0,1, o_EbmlString ) \
   XMAP_C_( ChapProcess, 0x6944,0,1, o_EbmlMaster ) \
   XMAP_C_( ChapProcessCodecID, 0x6055,1,0, o_EbmlUint ) \
   XMAP_C_( ChapProcessPrivate, 0x450d,0,0, o_EbmlBinary ) \
   XMAP_C_( ChapProcessCommand, 0x6911,0,1, o_EbmlMaster ) \
   XMAP_C_( ChapProcessTime, 0x6922,1,0, o_EbmlUint ) \
   XMAP_C_( ChapProcessData, 0x6933,1,0, o_EbmlBinary ) \
   XMAP_C_( Tags, 0x1254c367,0,1, o_EbmlMaster ) \
   XMAP_C_( Tag, 0x7373,1,1, o_EbmlMaster ) \
   XMAP_C_( Targets, 0x63c0,1,0, o_EbmlMaster ) \
   XMAP_C_( TargetTypeValue, 0x68ca,0,0, o_EbmlUint ) \
   XMAP_C_( TargetType, 0x63ca,0,0, o_EbmlString ) \
   XMAP_C_( TagTrackUID, 0x63c5,0,1, o_EbmlUint ) \
   XMAP_C_( TagEditionUID, 0x63c9,0,1, o_EbmlUint ) \
   XMAP_C_( TagChapterUID, 0x63c4,0,1, o_EbmlUint ) \
   XMAP_C_( TagAttachmentUID, 0x63c6,0,1, o_EbmlUint ) \
   XMAP_C_( SimpleTag, 0x67c8,1,1, o_EbmlMaster ) \
   XMAP_C_( TagName, 0x45a3,1,0, o_EbmlUtf8 ) \
   XMAP_C_( TagLanguage, 0x447a,1,0, o_EbmlString ) \
   XMAP_C_( TagLanguageIETF, 0x447b,0,0, o_EbmlString ) \
   XMAP_C_( TagDefault, 0x4484,1,0, o_EbmlUint ) \
   XMAP_C_( TagString, 0x4487,0,0, o_EbmlUtf8 ) \
   XMAP_C_( TagBinary, 0x4485,0,0, o_EbmlBinary )

#define XMAP_C_( Name, Id, MinOccurs, MaxOccurs, Type )           \
oEbmlDecl const Name = ebml_decl_o_( stringify_c_(Name), (oEbmlId){ .raw=Id }, MinOccurs, MaxOccurs, Type );

EBML_MKV_DECL_LIST_
#undef XMAP_C_

static oEbmlDeclSlice get_ebml_mkv_decl( oVarEbmlDeclSlice buf )
{
   oEbmlDeclSlice src = slice_c_( oEbmlDecl,
      Segment,
         SeekHead,
            Seek,
               SeekID,
               SeekPosition,
         Info,
            SegmentUID,
            SegmentFilename,
            PrevUID,
            PrevFilename,
            NextUID,
            NextFilename,
            SegmentFamily,
            ChapterTranslate,
               ChapterTranslateEditionUID,
               ChapterTranslateCodec,
               ChapterTranslateID,
            TimestampScale,
            Duration,
            DateUTC,
            Title,
            MuxingApp,
            WritingApp,
         Cluster,
            Timestamp,
            SilentTracks,
            SilentTrackNumber,
            Position,
            PrevSize,
            SimpleBlock,
            BlockGroup,
               Block,
               BlockVirtual,
               BlockAdditions,
                  BlockMore,
                     BlockAddID,
                     BlockAdditional,
               BlockDuration,
               ReferencePriority,
               ReferenceBlock,
               ReferenceVirtual,
               CodecState,
               DiscardPadding,
               Slices,
                  TimeSlice,
                     LaceNumber,
                     FrameNumber,
                     BlockAdditionID,
                     Delay,
                     SliceDuration,
               ReferenceFrame,
                  ReferenceOffset,
                  ReferenceTimestamp,
            EncryptedBlock,
         Tracks,
            TrackEntry,
               TrackNumber,
               TrackUID,
               TrackType,
               FlagEnabled,
               FlagDefault,
               FlagForced,
               FlagHearingImpaired,
               FlagVisualImpaired,
               FlagTextDescriptions,
               FlagOriginal,
               FlagCommentary,
               FlagLacing,
               MinCache,
               MaxCache,
               DefaultDuration,
               DefaultDecodedFieldDuration,
               TrackTimestampScale,
               TrackOffset,
               MaxBlockAdditionID,
               BlockAdditionMapping,
                  BlockAddIDValue,
                  BlockAddIDName,
                  BlockAddIDType,
                  BlockAddIDExtraData,
               Name,
               Language,
               LanguageIETF,
               CodecID,
               CodecPrivate,
               CodecName,
               AttachmentLink,
               CodecSettings,
               CodecInfoURL,
               CodecDownloadURL,
               CodecDecodeAll,
               TrackOverlay,
               CodecDelay,
               SeekPreRoll,
               TrackTranslate,
                  TrackTranslateEditionUID,
                  TrackTranslateCodec,
                  TrackTranslateTrackID,
               Video,
                  FlagInterlaced,
                  FieldOrder,
                  StereoMode,
                  AlphaMode,
                  OldStereoMode,
                  PixelWidth,
                  PixelHeight,
                  PixelCropBottom,
                  PixelCropTop,
                  PixelCropLeft,
                  PixelCropRight,
                  DisplayWidth,
                  DisplayHeight,
                  DisplayUnit,
                  AspectRatioType,
                  ColourSpace,
                  GammaValue,
                  FrameRate,
                  Colour,
                     MatrixCoefficients,
                     BitsPerChannel,
                     ChromaSubsamplingHorz,
                     ChromaSubsamplingVert,
                     CbSubsamplingHorz,
                     CbSubsamplingVert,
                     ChromaSitingHorz,
                     ChromaSitingVert,
                     Range,
                     TransferCharacteristics,
                     Primaries,
                     MaxCLL,
                     MaxFALL,
                     MasteringMetadata,
                        PrimaryRChromaticityX,
                        PrimaryRChromaticityY,
                        PrimaryGChromaticityX,
                        PrimaryGChromaticityY,
                        PrimaryBChromaticityX,
                        PrimaryBChromaticityY,
                        WhitePointChromaticityX,
                        WhitePointChromaticityY,
                        LuminanceMax,
                        LuminanceMin,
                  Projection,
                     ProjectionType,
                     ProjectionPrivate,
                     ProjectionPoseYaw,
                     ProjectionPosePitch,
                     ProjectionPoseRoll,
               Audio,
                  SamplingFrequency,
                  OutputSamplingFrequency,
                  Channels,
                  ChannelPositions,
                  BitDepth,
               TrackOperation,
                  TrackCombinePlanes,
                     TrackPlane,
                        TrackPlaneUID,
                        TrackPlaneType,
                  TrackJoinBlocks,
                     TrackJoinUID,
               TrickTrackUID,
               TrickTrackSegmentUID,
               TrickTrackFlag,
               TrickMasterTrackUID,
               TrickMasterTrackSegmentUID,
               ContentEncodings,
                  ContentEncoding,
                     ContentEncodingOrder,
                     ContentEncodingScope,
                     ContentEncodingType,
                     ContentCompression,
                        ContentCompAlgo,
                        ContentCompSettings,
                     ContentEncryption,
                        ContentEncAlgo,
                        ContentEncKeyID,
                        ContentEncAESSettings,
                           AESSettingsCipherMode,
                        ContentSignature,
                        ContentSigKeyID,
                        ContentSigAlgo,
                        ContentSigHashAlgo,
         Cues,
            CuePoint,
               CueTime,
               CueTrackPositions,
                  CueTrack,
                  CueClusterPosition,
                  CueRelativePosition,
                  CueDuration,
                  CueBlockNumber,
                  CueCodecState,
                  CueReference,
                     CueRefTime,
                     CueRefCluster,
                     CueRefNumber,
                     CueRefCodecState,
         Attachments,
            AttachedFile,
               FileDescription,
               FileName,
               FileMimeType,
               FileData,
               FileUID,
               FileReferral,
               FileUsedStartTime,
               FileUsedEndTime,
         Chapters,
            EditionEntry,
               EditionUID,
               EditionFlagHidden,
               EditionFlagDefault,
               EditionFlagOrdered,
               ChapterAtom,
                  ChapterUID,
                  ChapterStringUID,
                  ChapterTimeStart,
                  ChapterTimeEnd,
                  ChapterFlagHidden,
                  ChapterFlagEnabled,
                  ChapterSegmentUID,
                  ChapterSegmentEditionUID,
                  ChapterPhysicalEquiv,
                  ChapterTrack,
                     ChapterTrackUID,
                  ChapterDisplay,
                     ChapString,
                     ChapLanguage,
                     ChapLanguageIETF,
                     ChapCountry,
                  ChapProcess,
                     ChapProcessCodecID,
                     ChapProcessPrivate,
                     ChapProcessCommand,
                        ChapProcessTime,
                        ChapProcessData,
         Tags,
            Tag,
               Targets,
                  TargetTypeValue,
                  TargetType,
                  TagTrackUID,
                  TagEditionUID,
                  TagChapterUID,
                  TagAttachmentUID,
               SimpleTag,
                  TagName,
                  TagLanguage,
                  TagLanguageIETF,
                  TagDefault,
                  TagString,
                  TagBinary
   );

   buf.s = set_ebml_decl_slice_c( buf, src );
   if ( buf.s != src.s )
   {
      return (oEbmlDeclSlice)invalid_c_();
   }

   return as_c_( oEbmlDeclSlice, buf );
}

#endif