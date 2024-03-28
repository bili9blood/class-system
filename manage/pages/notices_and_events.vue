<script setup lang="ts">
definePageMeta({
  name: "公告·事件",
});

const { info } = storeToRefs(useClassStore());

const today = moment().format("YYYYMMDD");

function HandleRemoveNotice(idx: number) { info.value?.notices.splice(idx, 1); }
function HandleInsertNotice(idx: number) { info.value?.notices.splice(idx + 1, 0, { title: "", date: today, text: "", id: 0 }); }

function HandleRemoveEvent(idx: number) { info.value?.events.splice(idx, 1); }
function HandleInsertEvent(idx: number) { info.value?.events.splice(idx + 1, 0, { title: "", date: today, important: false, id: 0 }); }

function FormatDate(date: string) {
  return date.replace(/(\d{4})(\d{2})(\d{2})/, "$1-$2-$3");
}

function GetElidedText(text: string, max_len: number) {
  if (text.length > max_len)
    return `${text.substring(0, max_len)}...`;

  return text;
}
</script>

<template>
  <div>
    <q-card bg-secondary>
      <q-card-section>
        <q-btn outline icon="add" @click="HandleInsertNotice(-1)">
          添加公告
        </q-btn>
      </q-card-section>
      <q-card-section w-full overflow-x-auto>
        <q-markup-table flat min-w-160 justify-center bg-transparent>
          <thead font-bold>
            <tr>
              <th>标题</th>
              <th>日期</th>
              <th>内容</th>
              <th>操作</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="notice, idx in info?.notices" :key="notice.id">
              <td><q-input v-model="notice.title" outlined dense /></td>
              <td>
                <div flex justify-center>
                  <q-btn v-show="notice.date !== 'FOREVER'" flat dense icon="calendar_month" w-full>
                    <q-popup-proxy cover transition-show="scale" transition-hide="scale">
                      <q-date v-model="notice.date" mask="YYYYMMDD">
                        <div class="row items-center justify-end">
                          <q-btn v-close-popup label="关闭" color="primary" flat />
                        </div>
                      </q-date>
                    </q-popup-proxy>
                    <div>{{ FormatDate(notice.date) }}</div>
                  </q-btn>
                  <q-toggle
                    :model-value="notice.date === 'FOREVER'"
                    label="永久"
                    @update:model-value="(v) => notice.date = v ? 'FOREVER' : today"
                  />
                </div>
              </td>

              <td>
                <q-btn flat dense icon="edit" w-full>
                  <q-popup-proxy cover transition-show="scale" transition-hide="scale">
                    <q-input v-model="notice.text" autogrow outlined dense />
                  </q-popup-proxy>
                  <div>{{ GetElidedText(notice.text, 10) }}</div>
                </q-btn>
              </td>

              <td>
                <div flex justify-center>
                  <q-btn flat dense label="删除" @click="HandleRemoveNotice(idx)" />
                  <q-btn flat dense label="插入" @click="HandleInsertNotice(idx)" />
                </div>
              </td>
            </tr>
          </tbody>
        </q-markup-table>
      </q-card-section>
    </q-card>
    <br>
    <q-card bg-secondary>
      <q-card-section>
        <q-btn outline icon="add" @click="HandleInsertEvent(-1)">
          添加事件
        </q-btn>
      </q-card-section>
      <q-card-section w-full overflow-x-auto>
        <q-markup-table flat min-w-160 justify-center bg-transparent>
          <thead font-bold>
            <tr>
              <th>标题</th>
              <th>日期</th>
              <th>重要</th>
              <th>操作</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="event, idx in info?.events" :key="event.id">
              <td><q-input v-model="event.title" outlined dense /></td>
              <td>
                <div flex justify-center>
                  <q-btn flat dense icon="calendar_month" w-full>
                    <q-popup-proxy cover transition-show="scale" transition-hide="scale">
                      <q-date v-model="event.date" mask="YYYYMMDD">
                        <div class="row items-center justify-end">
                          <q-btn v-close-popup label="关闭" color="primary" flat />
                        </div>
                      </q-date>
                    </q-popup-proxy>
                    <div>{{ FormatDate(event.date) }}</div>
                  </q-btn>
                </div>
              </td>

              <td>
                <q-toggle v-model="event.important" w-full justify-center />
              </td>

              <td>
                <div flex justify-center>
                  <q-btn flat dense label="删除" @click="HandleRemoveEvent(idx)" />
                  <q-btn flat dense label="插入" @click="HandleInsertEvent(idx)" />
                </div>
              </td>
            </tr>
          </tbody>
        </q-markup-table>
      </q-card-section>
    </q-card>
  </div>
</template>
