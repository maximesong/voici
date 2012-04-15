#include "ImageFamily.h"

#include "Exceptions.h"

ImageFamily::ImageFamily(const QImage &originImage, const QString &familyName)
{
	setFamilyName(familyName);
	setOriginImage(originImage);
	initFamily();
}


ImageFamily::ImageFamily(const QString &originImageFilename, const QString &familyName)
{
	setFamilyName(familyName);
	loadOriginImage(originImageFilename);
	initFamily();
}


void ImageFamily::initFamily()
{
	m_dynamic_processer_list.clear();
	m_pre_processer_list.clear();
	m_pre_processer_list.fill(SharedImageProcesser(), PRE_PROCESSER_NR);
	m_post_processer_list.clear();
	m_post_processer_list.fill(SharedImageProcesser(), POST_PROCESSER_NR);
	m_dynamic_image_list.clear();
	m_pre_processed_image = m_post_processed_image 
		= m_dynamic_image = m_origin_image;
	m_dynamic_processer_index = -1;
}


/*
ImageFamily::ImageFamily(const ImageFamily &imageFamily)
{
}


ImageFamily ImageFamily::&operator=(const ImageFamily &imageFamily)
{
}
*/


QImage ImageFamily::getOriginImage() const
{
	return m_origin_image;
}


QImage ImageFamily::getCurrentImage() const
{
	return m_post_processed_image;
}


QString ImageFamily::getFamilyName() const
{
	return m_family_name;
}


QString ImageFamily::getDynamicProcesserName(int index) const
{
	if (index >= 0 && index < m_dynamic_processer_list.size())
		return m_dynamic_processer_list[index]->getProcesserName();
	else
		return "";
}


void ImageFamily::loadOriginImage(const QString &filename)
{
	m_origin_image.load(filename);
	if (m_origin_image.isNull())
		throw FileError();

	/* Always do the conversion may not be efficient, to be improved */
	if (m_origin_image.format() != QImage::Format_ARGB32)
		m_origin_image = m_origin_image.convertToFormat(QImage::Format_ARGB32);

	initFamily();
}


void ImageFamily::setOriginImage(const QImage &image)
{
	m_origin_image = image;
	initFamily();
}


void ImageFamily::setFamilyName(const QString &name)
{
	m_family_name = name;
}


void ImageFamily::pushDynamicImageProcesser(SharedImageProcessor processer)
{
	if (m_dynamic_processer_index + 1 < m_dynamic_image_list.size()) {
		int expired_processer_count = m_dynamic_processer_list.size() - 1 - 
			m_dynamic_processer_index;
		m_dynamic_processer_list.remove(m_dynamic_processer_index + 1,
						expired_processer_count);
	}
	m_dynamic_processer_list.push_back(processer);
	++m_dynamic_processer_index;
	applyAllProcessers();
}

void ImageFamily::popDynamicImageProcesser()
{
	if (m_dynamic_processer_index >= 0) {
		--m_dynamic_processer_index;
		applyAllProcessers();
	}
}

void ImageFamily::switchToDynamicProcess(int index)
{
	if (index >= -1 && index < m_dynamic_processer_list.size()) {
		m_dynamic_processer_index = index;
		applyAllProcessers();
	}
}

void ImageFamily::applyDynamicProcessers()
{
	m_dynamic_image = m_pre_processed_image;
	if (m_dynamic_processer_index == -1)
		return;
	else if (m_dynamic_processer_index < m_dynamic_image_list.size())
		m_dynamic_image = m_dynamic_image_list[m_dynamic_processer_index];
	else
		for (int i = m_dynamic_image_list.size();
		     i <= m_dynamic_processer_index; ++i) {
			m_dynamic_image = 
				m_dynamic_processer_list[i]->produceProcessedImage(
					m_dynamic_image);
			m_dynamic_image_list.push_back(m_dynamic_image);
		}
}


void ImageFamily::applyPostProcessers()
{
	m_post_processed_image = m_dynamic_image;
	for (int i = 0; i != m_post_processer_list.size(); ++i)
		if (! m_post_processer_list[i].isNull())
			m_post_processed_image = 
				m_post_processer_list[i]->produceProcessedImage(
					m_post_processed_image);
}


void ImageFamily::applyPreProcessers()
{
	m_pre_processed_image = m_origin_image;
	for (int i = 0; i != m_pre_processer_list.size(); ++i)
		if (! m_pre_processer_list[i].isNull())
			m_pre_processed_image = 
				m_pre_processer_list[i]->produceProcessedImage(
					m_pre_processed_image);
	m_dynamic_image_list.clear();
}


void ImageFamily::applyAllProcessers(bool needApplyPreProcessers)
{
	if (needApplyPreProcessers)
		applyPreProcessers();
	applyDynamicProcessers();
	applyPostProcessers();
}


void ImageFamily::setPreProcesser(PreProcesser id, SharedImageProcesser processer)
{
	m_pre_processer_list[id] = processer;
}
	
void ImageFamily::setPostProcesser(PostProcesser id, SharedImageProcesser processer)
{
	m_post_processer_list[id] = processer;
}
