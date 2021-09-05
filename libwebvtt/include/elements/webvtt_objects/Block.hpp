#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_BLOCK_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_BLOCK_HPP_

namespace webvtt {
/**
 * Base class for all webvtt elements.
 */
class Block {
 public:

  Block() = default;
  Block(const Block &) = delete;
  Block(Block &&) = delete;
  Block &operator=(const Block &) = delete;
  Block &operator=(Block &&) = delete;
  virtual ~Block() = default;
};
} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_WEBVTT_OBJECTS_BLOCK_HPP_
