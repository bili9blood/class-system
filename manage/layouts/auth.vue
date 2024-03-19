<template>
  <div h-screen w-screen overflow-hidden>
    <QLayout flex="~ col" h-full>
      <TheHeader :nav="false" />

      <QPageContainer flex-1>
        <div h-full w-full flex>
          <div hidden flex-1 sm:block />
          <div sm:w="45%" flex-2 h-full w-full bg-white px-4 py-8>
            <slot />
          </div>
          <div hidden flex-1 sm:block />
        </div>
      </QPageContainer>

      <PageFooter />
    </QLayout>
  </div>
</template>
